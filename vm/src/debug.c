/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:37:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/20 16:43:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_carriage(t_env *env, t_carriage *carriage)
{
	int i;

	ft_printf("Carriage %d:\n", carriage->id);
	ft_printf("Position: %d, byte: ", carriage->position);
	print_memory(env->field + carriage->position, 1);
	ft_printf("\nRegisters:\n");
	i = 0;
	while (i < REG_NUMBER)
	{
		ft_printf("[%d] = %d, ", i + 1, carriage->registers[i]);
		print_memory(carriage->registers + i, REG_SIZE);
		write(1, "\n", 1);
		i++;
	}
}