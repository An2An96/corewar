/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:17:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/26 14:20:01 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_sti(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned char	arg_type;
	unsigned char	reg;
	int				value[3];
	unsigned short	mempos;

	va_start(args, args_types);
	reg = va_arg(args, int);
	arg_type = ARG_TYPE(args_types, 1);
	value[0] = va_arg(args, int);
	if (arg_type == REG_CODE)
	{
		if (!get_reg_value(carriage, value[0], &value[0], PROC_ENDIAN))
		{
			va_end(args);
			return (-1);
		}
	}
	else if (arg_type == IND_CODE)
	{
		value[0] = get_mem_value(env, carriage, value[0], true);
		swap_bytes(&value[0], sizeof(int));
	}
	arg_type = ARG_TYPE(args_types, 2);
	value[1] = va_arg(args, int);
	if (arg_type == REG_CODE)
	{
		if (!get_reg_value(carriage, value[1], &value[1], PROC_ENDIAN))
		{
			va_end(args);
			return (-1);
		}
	}
	get_reg_value(carriage, reg, &value[2], BIG_END);
	mempos = set_mem_value(env, carriage, value[0] + value[1], value[2]);
	VERB_LEVEL(SHOW_OPS) &&
		ft_printf("\n%8 | -> store to %d + %d = %d (with pc and mod %d)",
		value[0], value[1], value[0] + value[1], mempos);
	va_end(args);
	return (-1);
}
