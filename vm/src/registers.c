/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:22:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/26 13:06:41 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

bool	get_reg_value(t_carriage *carriage, char idx, int *value, bool convert_endian)
{
	// ft_printf("get_reg_value %d %d %d\n", idx, *value, convert_endian);
	if (idx < 1 || idx > REG_NUMBER)
		return (false);
	// ft_printf("Old val: ");
	// print_memory(value, 4);
	// ft_printf("\n");
	*value = carriage->registers[idx - 1];
	if (convert_endian)
		swap_bytes(value, sizeof(int));
	// ft_printf("New val: ");
	// print_memory(value, 4);
	// ft_printf("\n");
	return (true);
}

bool	set_reg_value(t_carriage *carriage, char idx, int value, bool convert_endian)
{
	if (idx < 1 || idx > REG_NUMBER)
		return (false);
	if (convert_endian)
		swap_bytes(&value, sizeof(int));

	// ft_printf("[register %d] Old val: ", idx);
	// print_memory(&carriage->registers[idx - 1], 4);
	// write(1, "\n", 1);

	carriage->registers[idx - 1] = value;

	// ft_printf("[register %d] New val: ", idx);
	// print_memory(&carriage->registers[idx - 1], 4);
	// write(1, "\n", 1);
	return (true);
}
