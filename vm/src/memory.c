/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:23:15 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 18:23:20 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	calc_mem_addr(int start, int offset, bool truncat)
{
	int	mempos;

	truncat && (offset %= IDX_MOD);
	mempos = start + offset;
	(mempos < 0) && (mempos = MEM_SIZE - mempos);
	return (mempos);
}

int	get_mem_value(t_env *env, t_carriage *carriage, int offset, bool truncat)
{
	unsigned char	value[4];
	int				mempos;

	mempos = calc_mem_addr(carriage->position, offset, truncat);
	value[0] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[1] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[2] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[3] = *(env->field + mempos % MEM_SIZE);
	return (int)value;
}
