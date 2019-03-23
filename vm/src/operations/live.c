/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:13:09 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/23 17:58:39 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_live(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned int	player;

	va_start(args, args_types);
	player = va_arg(args, int);
	carriage->last_live_cycle = env->acount_cycles;
	env->rcount_lives++;
	// print_carriage(env, carriage);
	va_end(args);
	return (-1);
}
