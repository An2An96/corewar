/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:17:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 12:18:02 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_sti(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	int				value[2];
	unsigned short	mempos;

	value[0] = args[1].content;
	if (PROC_ENDIAN && (args[1].type == REG_CODE || args[1].type == IND_CODE))
		swap_bytes(&value[0], sizeof(int));
	value[1] = args[2].content;
	if (PROC_ENDIAN && args[2].type == REG_CODE)
		swap_bytes(&value[1], sizeof(int));
	mempos = set_mem_value(env, carriage, value[0] + value[1], args[0].content);
	VERB_LEVEL(SHOW_OPS) &&
		ft_printf("\n%8 | -> store to %d + %d = %d (with pc and mod %d)",
		value[0], value[1], value[0] + value[1], mempos);
	return (-1);
}
