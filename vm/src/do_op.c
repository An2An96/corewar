/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 15:35:18 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op_func	g_op_funcs[] = {
	NULL,
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};

t_op	*get_op(char op_code)
{
	int8_t i;

	if (op_code && op_code <= 0x10)
	{
		i = 0;
		while (g_op_tab[i].op_code)
		{
			if (g_op_tab[i].op_code == op_code)
				return (&g_op_tab[i]);
			i++;
		}
	}
	return (NULL);
}

int	get_cmd_length(t_op *op, unsigned char *mempos)
{
	int		len;
	int		i;
	uint8_t	args_types;
	uint8_t	arg_type;

	len = 1;
	if (op)
	{
		if (op->codage_octal)
		{
			args_types = *mempos;
			len++;
		}
		else
			args_types = T_DIR << 6;
		i = op->arg_count;
		while (i)
		{
			arg_type = ARG_TYPE(args_types, i - 1);
			arg_type == DIR_CODE && op->dir_ind_size && (arg_type = IND_CODE);
			if (arg_type == REG_CODE)
				len++;
			else if (arg_type == IND_CODE)
				len += 2;
			else if (arg_type == DIR_CODE)
				len += 4;
			i--;
		}
	}
	return (len);
}

inline static bool	is_arg_types_valid(t_op *op, uint8_t args_types)
{
	return (ARG_TYPE(args_types, 0) & op->arg_type[0]
		&& (op->arg_count < 2 || ARG_TYPE(args_types, 1) & op->arg_type[1])
		&& (op->arg_count < 3 || ARG_TYPE(args_types, 2) & op->arg_type[2]));
}

int		get_arg_value(t_carriage *carriage,
	t_arg_type type, bool dir_ind_size, unsigned char **mempos)
{
	int		value;
	short	short_arg;

	// type == DIR_CODE && dir_ind_size && (type = IND_CODE);
	if (type == REG_CODE)
	{
		value = *((unsigned char*)(*mempos));
		*mempos += sizeof(unsigned char);
	}
	else if (type == DIR_CODE)
	{
		if (dir_ind_size)
		{
			value = *((unsigned short*)(*mempos));
			*mempos += sizeof(unsigned short);
			// ft_printf("dir_ind_size:\n");
			// print_memory(&value, 4);
			// ft_putchar('\n');
		}
		else
		{
			value = *((unsigned int*)(*mempos));
			*mempos += sizeof(unsigned int);
			// ft_printf("dir_size:\n");
			// print_memory(&value, 4);
			// ft_putchar('\n');
		}
	}
	else if (type == IND_CODE)
	{
		short_arg = *((unsigned short*)(*mempos));
		if (PROC_ENDIAN)
			swap_bytes(&short_arg, sizeof(unsigned short));
		*mempos += sizeof(unsigned short);
		value = short_arg;
	}
	return (value);
}

int	get_arg_content(t_env *env, t_carriage *carriage, bool dir_ind_size, t_arg *arg)
{
	short	short_arg;

	if (arg->type == REG_CODE)
	{
		return (get_reg_value(carriage, arg->value, &arg->content, false));
	}
	else if (arg->type == IND_CODE)
	{
		arg->content = get_mem_value(env, carriage, arg->value, true);
		return (true);
	}
	else if (arg->type == DIR_CODE)
	{
		if (dir_ind_size)
		{
			short_arg = arg->value;
			if (PROC_ENDIAN)
				swap_bytes(&short_arg, sizeof(short));
			arg->content = short_arg;
		}
		else
		{
			arg->content = arg->value;
			if (PROC_ENDIAN)
				swap_bytes(&arg->content, sizeof(int));
		}
		return (true);
	}
	return (false);
}

bool	get_args(
	t_env *env, t_carriage *carriage, unsigned char *mempos, t_arg **args)
{
	t_op		*op;
	uint8_t		args_types;
	int8_t		i;

	*args = NULL;
	if ((op = get_op(carriage->op_code)))
	{
		if (op->codage_octal)
		{
			args_types = *mempos;
			if (!is_arg_types_valid(op, args_types))
				return (false);
			mempos++;
		}
		else
			args_types = DIR_CODE << 6;
		SECURE_MALLOC(*args = ft_memalloc(op->arg_count * sizeof(t_arg)));
		i = 0;
		while (i < op->arg_count)
		{
			(*args)[i].type = ARG_TYPE(args_types, i);
			(*args)[i].value = get_arg_value(
				carriage, (*args)[i].type, op->dir_ind_size, &mempos);
			if (!get_arg_content(env, carriage, op->dir_ind_size, (*args) + i))
				return (false);
			// ft_printf("type: %d, value: %x, content: %x\n", (*args)[i].type, (*args)[i].value, (*args)[i].content);
			i++;
		}
		return (true);
	}
	return (false);
}

int	do_op(t_env *env, t_carriage *carriage, unsigned char *mempos)
{
	t_op	*op;
	t_arg	*args;
	int		zjmp;
	int		len;

	zjmp = -1;
	mempos++;
	if ((op = get_op(carriage->op_code)))
	{
		len = get_cmd_length(op, mempos);
		if (get_args(env, carriage, mempos, &args))
		{
			if (VERB_LEVEL(SHOW_OPS))
				print_do_op(carriage->id, op->cmd, args, op->arg_count);
			zjmp = g_op_funcs[carriage->op_code](env, carriage, 0, args);
			VERB_LEVEL(SHOW_OPS) && write(1, "\n", 1);
		}
		if (VERB_LEVEL(SHOW_PC_MOVES) && zjmp == -1)
			print_move(env, carriage->position, len);
		zjmp != -1 && (len = zjmp);
	}
	else
	{
		len = 1;
	}
	return (calc_mem_addr(carriage->position, len, true));
}
