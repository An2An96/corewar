/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 16:00:41 by rschuppe         ###   ########.fr       */
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

bool	get_arg(char type, bool dir_ind_size, unsigned char **mempos, int *value)
{
	short	short_arg;

	type == DIR_CODE && dir_ind_size && (type = IND_CODE);
	if (type == REG_CODE)
	{
		*value = *((unsigned char*)(*mempos));
		if (PROC_ENDIAN)
			swap_bytes(value, sizeof(unsigned char));
		*mempos += sizeof(unsigned char);
		if (*value < 1 || *value > REG_NUMBER)
			return (false);
	}
	else if (type == IND_CODE)
	{
		short_arg = *((unsigned short*)(*mempos));
		if (PROC_ENDIAN)
			swap_bytes(&short_arg, sizeof(unsigned short));
		*mempos += sizeof(unsigned short);
		*value = short_arg;
	}
	else if (type == DIR_CODE)
	{
		*value = *((unsigned int*)(*mempos));
		if (PROC_ENDIAN)
			swap_bytes(value, sizeof(unsigned int));
		*mempos += sizeof(unsigned int);
	}
	return (true);
}

inline static bool	is_arg_types_valid(t_op *op, uint8_t args_types)
{
	return (ARG_TYPE(args_types, 0) & op->arg_type[0]
		&& (op->arg_count < 2 || ARG_TYPE(args_types, 1) & op->arg_type[1])
		&& (op->arg_count < 3 || ARG_TYPE(args_types, 2) & op->arg_type[2]));
}

/*

Если данный код корректен и указывает, что среди аргументов операции есть регистр, необходимо также убедиться в корректности номера регистра.

Если все необходимые проверки были успешно пройдены, нужно выполнить операцию и передвинуть каретку на следующую позицию.

Если же код операции ошибочен, необходимо просто переместить каретку на следующий байт.

Если с самим кодом все нормально, но код типов аргументов или же номер регистра ошибочен, нужно пропустить данную операцию вместе с кодом типов аргументов и самими аргументами.

*/

int	do_op(t_env *env, t_carriage *carriage, unsigned char *mempos)
{
	t_op	*op;
	int		args[3];
	uint8_t	args_types;
	int		zjmp;
	int		len;

	mempos++;
	if ((op = get_op(carriage->op_code)))
	{
		len = get_cmd_length(op, mempos);
		if (op->codage_octal)
		{
			args_types = *mempos;
			if (!is_arg_types_valid(op, args_types))
				return (calc_mem_addr(carriage->position, len, false));
			mempos++;
		}
		else
			args_types = T_DIR << 6;
		if (get_arg(ARG_TYPE(args_types, 0), op->dir_ind_size,
			&mempos, &args[0])
			&& (op->arg_count < 2 || get_arg(ARG_TYPE(args_types, 1),
				op->dir_ind_size, &mempos, &args[1]))
			&& (op->arg_count < 3 || get_arg(ARG_TYPE(args_types, 2),
				op->dir_ind_size, &mempos, &args[2])))
		{
			if (op->arg_count == 1)
			{
				VERB_LEVEL(SHOW_OPS) &&
					ft_printf("P%5d | %s %s%d",
					carriage->id, op->cmd,
					ARG_TYPE(args_types, 0) == REG_CODE ? "r" : "", args[0]);
				zjmp = g_op_funcs[carriage->op_code](
					env, carriage, args_types, args[0]);
			}
			else if (op->arg_count == 2)
			{
				VERB_LEVEL(SHOW_OPS) &&
					ft_printf("P%5d | %s %s%d %s%d",
					carriage->id, op->cmd,
					ARG_TYPE(args_types, 0) == REG_CODE ? "r" : "", args[0],
					ARG_TYPE(args_types, 1) == REG_CODE ? "r" : "", args[1]);
				zjmp = g_op_funcs[carriage->op_code](
					env, carriage, args_types, args[0], args[1]);
			}
			else if (op->arg_count == 3)
			{
				VERB_LEVEL(SHOW_OPS) &&
					ft_printf("P%5d | %s %s%d %s%d %s%d",
					carriage->id, op->cmd,
					ARG_TYPE(args_types, 0) == REG_CODE ? "r" : "", args[0],
					ARG_TYPE(args_types, 1) == REG_CODE ? "r" : "", args[1],
					ARG_TYPE(args_types, 2) == REG_CODE ? "r" : "", args[2]);
				zjmp = g_op_funcs[carriage->op_code](
					env, carriage, args_types, args[0], args[1], args[2]);	
			}
			VERB_LEVEL(SHOW_OPS) && write(1, "\n", 1);
		}
		if (VERB_LEVEL(SHOW_PC_MOVES) && zjmp == -1)
			print_move(env, carriage->position, len);
		zjmp != -1 && (len = zjmp);
	}
	else
		len = 1;
	return (calc_mem_addr(carriage->position, len, false));
}
