/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:32:44 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 15:20:49 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_xor(t_env *env, t_carriage *carriage, int args_types, ...)
{	
	va_list			args;
	int				value[3];
	unsigned char	arg_type;
	int				res_reg;

	va_start(args, args_types);
	arg_type = ARG_TYPE(args_types, 0);
	value[0] = va_arg(args, int);
	if (arg_type == REG_CODE)
		get_reg_value(carriage, value[0], &value[0], BIG_END);
	else if (arg_type == IND_CODE)
		value[0] = *((unsigned int*)(carriage->position + value[0] % IDX_MOD));

	arg_type = ARG_TYPE(args_types, 1);
	value[1] = va_arg(args, int);
	if (arg_type == REG_CODE)
		get_reg_value(carriage, value[1], &value[1], BIG_END);
	else if (arg_type == IND_CODE)
		value[1] = *((unsigned int*)(carriage->position + value[1] % IDX_MOD));
	res_reg = va_arg(args, int);

	value[2] = value[0] ^ value[1];
	set_reg_value(carriage, res_reg, value[2], BIG_END);
	carriage->carry = !value[2];
	// ft_printf("op_and, arg1: %d, arg2: %d, arg3: %d\n", arg1, arg2, arg3);
	va_end(args);
	return (-1);
}
