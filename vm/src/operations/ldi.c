/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:26:57 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 14:06:36 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_ldi(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	int				value[2];
	unsigned int	mempos;

	value[0] = args[0].content;
	if (args[0].type == REG_CODE || args[0].type == IND_CODE)
	{
		if (PROC_ENDIAN)
			swap_bytes(&value[0], sizeof(value[0]));
	}
	value[1] = args[1].content;
	if (args[1].type == REG_CODE)
	{
		if (PROC_ENDIAN)
			swap_bytes(&value[1], sizeof(value[1]));
	}
	mempos = calc_mem_addr(carriage->position, value[0] + value[1], true);
	set_reg_value(carriage, args[2].value,
		get_mem_value(env, carriage, value[0] + value[1], true), false);
	VERB_LEVEL(SHOW_OPS) &&
		ft_printf("\n%8 | -> load from %d + %d = %d (with pc and mod %d)",
		value[0], value[1], value[0] + value[1], mempos);
	// print_carriage(env, carriage);
	return (-1);
}
