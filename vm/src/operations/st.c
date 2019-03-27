/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:15:01 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 12:32:04 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_st(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	if (args[1].type == REG_CODE)
		set_reg_value(carriage, args[1].value, args[0].content, false);
	else
		set_mem_value(env, carriage, args[1].value, args[0].content);
	return (-1);
}
