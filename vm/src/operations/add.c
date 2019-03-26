/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:22:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/26 13:07:02 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_add(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list		args;
	int			value[2];

	va_start(args, args_types);
	// print_carriage(env, carriage);
	if (get_reg_value(carriage, va_arg(args, int), &value[0], PROC_ENDIAN)
		&& get_reg_value(carriage, va_arg(args, int), &value[1], PROC_ENDIAN))
	{
		// print_memory(&value[0], 4);
		// write(1, "\n", 1);
		// print_memory(&value[1], 4);
		// write(1, "\n", 1);
		// ft_printf("%d + %d = ", value[0], value[1]);
		value[0] += value[1];
		// ft_printf("%d\n", value[0]);
		// print_memory(&value[0], 4);
		// write(1, "\n", 1);
		if (set_reg_value(carriage, va_arg(args, int), value[0], PROC_ENDIAN))
			carriage->carry = !value[0];
	}
	// print_carriage(env, carriage);
	va_end(args);
	return (-1);
}
