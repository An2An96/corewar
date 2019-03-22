/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 16:37:12 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/21 17:36:30 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_champion(t_champion *champion)
{
	ft_printf("\nChamp:\nName: %s\nComment: %s\nSize exec: %u\n",
		champion->prog_name, champion->comment, champion->prog_size);
	print_memory(champion->exec_code, champion->prog_size);
	ft_putchar('\n');
}

void	print_carriage(t_env *env, t_carriage *carriage)
{
	int i;
	int val;

	ft_printf("Carriage %d:\n", carriage->id);
	ft_printf("Position: %d, byte: ", carriage->position);
	print_memory(env->field + carriage->position, 1);
	ft_printf("\nLast_live_cycle: %d\n", carriage->last_live_cycle);
	ft_printf("Carry: %d\n", carriage->carry);
	ft_printf("Registers:\n");
	i = 0;
	while (i < REG_NUMBER)
	{
		val = carriage->registers[i];
		swap_bytes(&val, sizeof(int));
		ft_printf("[%02d] = %10d, ", i + 1, val);
		print_memory(&val, REG_SIZE);
		write(1, "\n", 1);
		i++;
	}
}
