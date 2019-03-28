/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:21:10 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 19:25:53 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_fork(t_env *env, t_carriage *carriage, t_arg *args)
{
	int		new_pos;

	new_pos = calc_mem_addr(carriage->position, args[0].content, true);
	create_carriage(env, carriage, new_pos);
	VERB_LEVEL(SHOW_OPS) && ft_printf("P%5d | fork %d (%d)\n",
		carriage->id, args[0].content, new_pos);
	return (-1);
}
