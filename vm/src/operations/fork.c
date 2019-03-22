/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:21:10 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 17:53:10 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_fork(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list	args;
	int		new_pos;

	va_start(args, args_types);
	create_carriage(env, carriage,
		calc_mem_addr(carriage->position, va_arg(args, int), true));
	va_end(args);
	return (-1);
}
