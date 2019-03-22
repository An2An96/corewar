/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:37:05 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 21:08:54 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_lfork(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list	args;

	va_start(args, args_types);
	create_carriage(env, carriage,
		calc_mem_addr(carriage->position, va_arg(args, int), false));
	va_end(args);
	return (-1);
}
