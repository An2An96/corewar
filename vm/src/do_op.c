/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/23 20:30:15 by rschuppe         ###   ########.fr       */
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

unsigned int	get_arg(char type, bool dir_ind_size, unsigned char **mempos)
{
	int arg;
	short short_arg;

	if (type == REG_CODE)
	{
		// print_memory(*mempos, 1);	ft_printf("\n");
		arg = *((unsigned char*)(*mempos));
		swap_bytes(&arg, sizeof(unsigned char));
		*mempos += sizeof(unsigned char);
		// print_memory(&arg, 4);	ft_printf("\n");
		// ft_printf("REG_CODE: %d\n", arg);
	}
	else if (type == IND_CODE || dir_ind_size)
	{
		// print_memory(*mempos, 2);	ft_printf("\n");
		short_arg = *((unsigned short*)(*mempos));
		swap_bytes(&short_arg, sizeof(unsigned short));
		*mempos += sizeof(unsigned short);
		// print_memory(&short_arg, 2);	ft_printf("\n");
		arg = short_arg;
		// ft_printf("IND_CODE: %d\n", (int)arg);
	}
	else if (type == DIR_CODE)
	{
		// print_memory(*mempos, 4);	ft_printf("\n");
		arg = *((unsigned int*)(*mempos));
		swap_bytes(&arg, sizeof(unsigned int));
		*mempos += sizeof(unsigned int);
		// print_memory(&arg, 4);	ft_printf("\n");
		// ft_printf("DIR_CODE: %u 123\n", arg);
	}
	return (arg);
}

/*

Если данный код корректен и указывает, что среди аргументов операции есть регистр, необходимо также убедиться в корректности номера регистра.

Если все необходимые проверки были успешно пройдены, нужно выполнить операцию и передвинуть каретку на следующую позицию.

Если же код операции ошибочен, необходимо просто переместить каретку на следующий байт.

Если с самим кодом все нормально, но код типов аргументов или же номер регистра ошибочен, нужно пропустить данную операцию вместе с кодом типов аргументов и самими аргументами.

*/

unsigned char	*do_op(t_env *env, t_carriage *carriage, unsigned char *mempos)
{
	t_op			*op;
	int				args[3];
	unsigned char	args_types;
	bool			invalid_args;
	int				new_pos;

	char *arg_type_names[] = { "", "REG_CODE", "DIR_CODE", "IND_CODE" };

	if (env->acount_cycles == 104830)
		new_pos = -1;

	// write(1, "1\n", 2);
	mempos++;
	if (env->field[carriage->position] && env->field[carriage->position] <= 0x10)
	{
		op = get_op(carriage->op_code);
		if (op->codage_octal)
		{
			args_types = *mempos;
			invalid_args = (!(ARG_TYPE(args_types, 0) & op->arg_type[0]
				&& (op->arg_count < 2 || ARG_TYPE(args_types, 1) & op->arg_type[1])
				&& (op->arg_count < 3 || ARG_TYPE(args_types, 2) & op->arg_type[2])));
			mempos++;
		}
		else
			args_types = T_DIR << 6;
		args[0] = get_arg(ARG_TYPE(args_types, 0), op->dir_ind_size, &mempos);
		if (op->arg_count > 1)
			args[1] = get_arg(ARG_TYPE(args_types, 1), op->dir_ind_size, &mempos);
		if (op->arg_count > 2)
			args[2] = get_arg(ARG_TYPE(args_types, 2), op->dir_ind_size, &mempos);
		if (!invalid_args)
		{
			if (op->arg_count == 1)
			{
				ft_printf("[Cycle: %d] CALL CMD: %s [%d (%s)]\n",
					env->acount_cycles, op->cmd, args[0], arg_type_names[ARG_TYPE(args_types, 0)]);
				new_pos = g_op_funcs[carriage->op_code](
					env, carriage, args_types, args[0]);
			}
			else if (op->arg_count == 2)
			{
				ft_printf("[Cycle: %d] CALL CMD: %s [%d (%s), %d (%s)]\n",
					env->acount_cycles, op->cmd,
					args[0], arg_type_names[ARG_TYPE(args_types, 0)],
					args[1], arg_type_names[ARG_TYPE(args_types, 1)]);
				new_pos = g_op_funcs[carriage->op_code](
					env, carriage, args_types, args[0], args[1]);
			}
			else if (op->arg_count == 3)
			{
				ft_printf("[Cycle: %d] CALL CMD: %s [%d (%s), %d (%s), %d (%s)]\n",
					env->acount_cycles, op->cmd,
					args[0], arg_type_names[ARG_TYPE(args_types, 0)],
					args[1], arg_type_names[ARG_TYPE(args_types, 1)],
					args[2], arg_type_names[ARG_TYPE(args_types, 2)]);
				new_pos = g_op_funcs[carriage->op_code](
					env, carriage, args_types, args[0], args[1], args[2]);
			}
		}
		else
			new_pos = -1;
		set_carriage_pos(carriage, (new_pos != -1) ? new_pos : (mempos - env->field));
	}
	return (mempos);
}