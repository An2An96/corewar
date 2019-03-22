/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:23:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 17:36:32 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_sub(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list		args;
	int			value[2];
	int			res_reg;

	va_start(args, args_types);
	// value[0] = va_arg(args, int);
	// ft_printf("reg 1 idx: %d, ", value[0]);
	get_reg_value(carriage, va_arg(args, int), &value[0], PROC_ENDIAN);
	// ft_printf("value: %d\n", value[0]);
	// value[1] = va_arg(args, int);
	// ft_printf("reg 2 idx: %d, ", value[1]);
	get_reg_value(carriage, va_arg(args, int), &value[1], PROC_ENDIAN);
	// ft_printf("value: %d\n", value[1]);
	res_reg = va_arg(args, int);
	// ft_printf("res reg idx: %d, value: %d | ", res_reg, carriage->registers[res_reg]);
	// print_memory(&carriage->registers[res_reg], 4); write(1, "\n", 1);
	value[0] -= value[1];
	set_reg_value(carriage, res_reg, value[0], PROC_ENDIAN);
	carriage->carry = !value[0];
	print_carriage(env, carriage);
	va_end(args);
	return (-1);
}