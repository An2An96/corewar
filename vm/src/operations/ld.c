/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:13:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 14:14:00 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_ld(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	int value;

	value = (args[0].type == DIR_CODE) ? args[0].value : args[0].content;
	if (set_reg_value(carriage, args[1].value, value, false))
		carriage->carry = !value;
	return (-1);
}
