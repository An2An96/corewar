/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:23:15 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/28 15:05:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	calc_mem_addr(int start, int offset, bool truncat)
{
	int	mempos;

	truncat && (offset %= IDX_MOD);
	mempos = (start + offset) % MEM_SIZE;
	(mempos < 0) && (mempos = MEM_SIZE + mempos);
	return (mempos);
}

int	get_mem_value_ex(t_env *env, int mempos, int bytes, bool convert_endian)
{
	int	i;
	int	result;

	// ft_printf("get_mem_value_ex mempos %d, bytes %d\n", mempos, bytes);
	i = 0;
	result = 0;
	if (convert_endian)
	{
		while (i < bytes)
		{
			// ft_printf("convert: %x\n", *(env->field + (mempos + bytes - 1 - i) % MEM_SIZE) << (8 * i));
			result |= *(env->field + (mempos + bytes - 1 - i) % MEM_SIZE) << (8 * i);
			// print_memory(&result, 4);
			// ft_putchar('\n');
			i++;
		}
	}
	else
	{
		while (i < bytes)
		{
			// ft_printf("no convert: %x << %d\n", *(env->field + (mempos + i) % MEM_SIZE), (8 * i));
			result |= *(env->field + (mempos + i) % MEM_SIZE) << (8 * i);
			// print_memory(&result, 4);
			// ft_putchar('\n');
			i++;
		}
	}
	if (result >> ((4 - bytes) * 8 - 1) & 1)
	{
		i = 0;
		while (i < (4 - bytes))
		{
			result |= 0xFF << (8 * (bytes + i));
			i++;
		}
	}
	// print_memory(&result, 4);
	// ft_printf("result %d\n", result);
	return (result);
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
