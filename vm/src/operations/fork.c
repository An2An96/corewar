/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:21:10 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/26 14:26:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_fork(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list	args;
	int		new_pos;

	va_start(args, args_types);
	new_pos = calc_mem_addr(carriage->position, va_arg(args, int), true);
	create_carriage(env, carriage, new_pos);
	if (VERB_LEVEL(SHOW_OPS))
	{
		write(1, " (", 2);
		ft_putnbr(new_pos);
		write(1, ")", 1);
	}
	va_end(args);
	return (-1);
}
