/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:22:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 13:38:16 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_add(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list		args;
	int			value[3];
	int			res_reg;

	ft_printf("op_add\n");

	va_start(args, args_types);

	value[0] = va_arg(args, int);
	ft_printf("reg 1 idx: %d, ", value[0]);
	get_reg_value(carriage, value[0], &value[0], PROC_ENDIAN);
	ft_printf("value: %d\n", value[0]);
	value[1] = va_arg(args, int);
	ft_printf("reg 2 idx: %d, ", value[1]);
	get_reg_value(carriage, value[1], &value[1], PROC_ENDIAN);
	ft_printf("value: %d\n", value[1]);
	res_reg = va_arg(args, int);
	ft_printf("res reg idx: %d, value: %d | ", res_reg, carriage->registers[res_reg]);
	print_memory(&carriage->registers[res_reg], 4); write(1, "\n", 1);
	// get_reg_value(carriage, value[2], &value[2], PROC_ENDIAN);

	value[0] += value[1];
	carriage->carry = !value[0];

	swap_bytes(&value[0], sizeof(value[0]));

	carriage->registers[res_reg] = value[0];
	ft_printf("res reg result value: %d | ", carriage->registers[res_reg]);
	print_memory(&carriage->registers[res_reg], 4); write(1, "\n", 1);

	va_end(args);
	return (-1);
}
