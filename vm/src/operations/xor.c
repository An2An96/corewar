/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:32:44 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 14:27:57 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_xor(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	int				value[3];

	value[0] = args[0].content;
	if (PROC_ENDIAN && args[0].type == REG_CODE || args[0].type == IND_CODE)
		swap_bytes(&value[0], sizeof(value[0]));
	value[1] = args[1].content;
	if (PROC_ENDIAN && args[1].type == REG_CODE || args[1].type == IND_CODE)
		swap_bytes(&value[1], sizeof(value[1]));
	value[2] = value[0] ^ value[1];
	if (set_reg_value(carriage, args[2].value, value[2], BIG_END))
		carriage->carry = !value[2];
	return (-1);
}
