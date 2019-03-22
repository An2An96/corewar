/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:22:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 20:24:30 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_add(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list		args;
	int			value[2];

	va_start(args, args_types);
	if (get_reg_value(carriage, va_arg(args, int), &value[0], PROC_ENDIAN)
		&& get_reg_value(carriage, va_arg(args, int), &value[1], PROC_ENDIAN))
	{
		value[0] += value[1];
		if (set_reg_value(carriage, va_arg(args, int), value[0], PROC_ENDIAN))
			carriage->carry = !value[0];
	}
	print_carriage(env, carriage);
	va_end(args);
	return (-1);
}
