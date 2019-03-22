/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:36:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 17:47:55 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_lldi(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned char	arg_type;
	unsigned char	reg_idx;
	int				value[2];

	va_start(args, args_types);
	arg_type = ARG_TYPE(args_types, 0);
	value[0] = va_arg(args, int);
	if (arg_type == REG_CODE)
	{
		if (!get_reg_value(carriage, value[0], &value[0], PROC_ENDIAN))
			return (-1);
	}
	else if (arg_type == IND_CODE)
	{
		value[0] = get_mem_value(env, carriage, value[0], true);
		swap_bytes(&value[0], sizeof(int));
	}
	value[1] = va_arg(args, int);
	if (ARG_TYPE(args_types, 1) == REG_CODE
		&& !get_reg_value(carriage, value[1], &value[1], PROC_ENDIAN))
		return (-1);
	reg_idx = va_arg(args, int);
	set_reg_value(carriage,
		reg_idx,
		get_mem_value(env, carriage, value[0] + value[1], false),
		BIG_END);
	va_end(args);
	return (-1);
}
