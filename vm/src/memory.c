/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:23:15 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 13:35:53 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	calc_mem_addr(int start, int offset, bool truncat)
{
	int	mempos;

	truncat && (offset %= IDX_MOD);
	mempos = start + offset;
	(mempos < 0) && (mempos = MEM_SIZE + mempos);
	return (mempos);
}

int	get_mem_value(t_env *env, t_carriage *carriage, int offset, bool truncat)
{
	unsigned char	value[4];
	int				mempos;

	// ft_printf("get_mem_value cur pos: %d, offset: %d, truncat: %d\n",
	// 	carriage->position, offset, truncat);

	mempos = calc_mem_addr(carriage->position, offset, truncat);

	// ft_printf("mempos = %d\n", mempos);

	value[0] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[1] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[2] = *(env->field + mempos % MEM_SIZE);
	mempos++;
	value[3] = *(env->field + mempos % MEM_SIZE);

	// print_memory(&value, 4);
	// write(1, "\n", 1);

	return (*((int*)value));
}

int	set_mem_value(t_env *env, t_carriage *carriage, int offset, int value)
{
	int mempos;

	// print_memory(&value, 4);
	// write(1, "\n", 1);

	// ft_printf("set_mem_value cur pos: %d, offset: %d, value: %d\n",
	// 	carriage->position, offset, value);

	mempos = calc_mem_addr(carriage->position, offset, true);

	// ft_printf("mempos = %d\n", mempos);

	// print_memory(env->field + mempos, 4);
	// write(1, "\n", 1);

	env->field[mempos] = (unsigned char)((value) & 0xFF);
	mempos++;
	env->field[mempos % MEM_SIZE] = (unsigned char)((value >> 8) & 0xFF);
	mempos++;
	env->field[mempos % MEM_SIZE] = (unsigned char)((value >> 16) & 0xFF);
	mempos++;
	env->field[mempos % MEM_SIZE] = (unsigned char)(value >> 24);
	mempos++;

	// print_memory(env->field + mempos - 4, 4);
	// write(1, "\n", 1);
	return (mempos - 4);
}
