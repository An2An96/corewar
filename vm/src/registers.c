/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:22:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 13:40:45 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

bool	get_reg_value(t_carriage *carriage, char idx, int *value, bool endian)
{
	if (idx < 1 || idx > REG_NUMBER)
		return (false);
	*value = carriage->registers[idx - 1];
	if (endian == LITTLE_END)
		swap_bytes(value, sizeof(int));
	return (true);
}

bool	set_reg_value(t_carriage *carriage, char idx, int value, bool endian)
{
	if (idx < 1 || idx > REG_NUMBER)
		return (false);
	if (endian == LITTLE_END)
		swap_bytes(&value, sizeof(int));
	carriage->registers[idx - 1] = value;
	carriage->carry = !value;
	return (true);
}
