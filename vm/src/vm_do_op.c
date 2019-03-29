/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 08:52:54 by rschuppe         ###   ########.fr       */
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

inline static void	get_cmd_length_helper(
	unsigned char mempos, int codage_octal, uint8_t *args_types, int *len)
{
	if (codage_octal)
	{
		*args_types = mempos;
		(*len)++;
	}
	else
		*args_types = T_DIR << 6;
}

static int			get_cmd_length(t_op *op, unsigned char mempos)
{
	int		len;
	int		i;
	uint8_t	args_types;
	uint8_t	arg_type;

	len = 1;
	if (op)
	{
		get_cmd_length_helper(mempos, op->codage_octal, &args_types, &len);
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

int					vm_do_op(t_env *env, t_carriage *carriage)
{
	t_op	*op;
	t_arg	*args;
	int		zjmp;
	int		len;

	len = 1;
	zjmp = -1;
	if ((op = get_op(carriage->op_code)))
	{
		len = get_cmd_length(op, *(env->field + carriage->position + 1));
		if (vm_get_args(env, carriage, &args))
			zjmp = g_op_funcs[carriage->op_code](env, carriage, args);
		if (args)
			free(args);
		if (VERB_LEVEL(SHOW_PC_MOVES) && zjmp == -1)
			print_move(env, carriage->position, len);
	}
	carriage->position = zjmp != -1 ?
		zjmp : calc_mem_addr(carriage->position, len, true);
	return (1);
}
