/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:13:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/26 13:06:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_ld(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	int	value;

	va_start(args, args_types);
	value = va_arg(args, int);
	if (ARG_TYPE(args_types, 0) == IND_CODE)
		value = get_mem_value(env, carriage, value, true);
	// print_memory(&value, 4);
	// write(1, "\n", 1);
	if (set_reg_value(carriage, va_arg(args, int), value, BIG_ENDIAN))
		carriage->carry = !value;
	// print_carriage(env, carriage);
	va_end(args);
	return (-1);
}
