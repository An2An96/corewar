/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:13:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 13:29:33 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_ld(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned int	value;
	unsigned char	reg_idx;

	va_start(args, args_types);
	value = va_arg(args, int);
	reg_idx = va_arg(args, int);

	if (ARG_TYPE(args_types, 0) == T_IND)
		value = *(unsigned int*)(env->field + carriage->position + value % IDX_MOD);

	set_reg_value(carriage, reg_idx, value, BIG_ENDIAN);
	// carriage->registers[reg] = value;
	// carriage->carry = !value;
	ft_printf("load op call, value: %d, reg: %d\n", value, reg_idx);
	print_carriage(env, carriage);
	va_end(args);
	return (-1);
}
