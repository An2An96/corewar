/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:37:40 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 17:55:48 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_aff(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list	args;
	int		value;

	va_start(args, args_types);
	get_reg_value(carriage, va_arg(args, int), &value, PROC_ENDIAN);
	write(1, (char*)&value, 1);
	va_end(args);
	return (-1);
}
