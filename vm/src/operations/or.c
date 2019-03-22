/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:32:29 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 21:28:41 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_or(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned char	arg_type;
	int				value[3];
	int				res_reg;

	va_start(args, args_types);
	arg_type = ARG_TYPE(args_types, 0);
	value[0] = va_arg(args, int);
	if (arg_type == REG_CODE)
	{
		if (!get_reg_value(carriage, value[0], &value[0], BIG_END))
		{
			va_end(args);
			return (-1);
		}
	}
	else if (arg_type == IND_CODE)
		value[0] = get_mem_value(env, carriage, value[0], true);
	arg_type = ARG_TYPE(args_types, 1);
	value[1] = va_arg(args, int);
	if (arg_type == REG_CODE)
	{
		if (!get_reg_value(carriage, value[1], &value[1], BIG_END))
		{
			va_end(args);
			return (-1);
		}
	}
	else if (arg_type == IND_CODE)
		value[1] = get_mem_value(env, carriage, value[1], true);
	res_reg = va_arg(args, int);
	value[2] = value[0] | value[1];
	if (set_reg_value(carriage, res_reg, value[2], BIG_END))
		carriage->carry = !value[2];
	va_end(args);
	return (-1);
}
