/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:17:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 17:58:10 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_sti(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned char	arg_type;
	unsigned char	reg;
	int				value[2];
	unsigned int	mempos;

	va_start(args, args_types);
	reg = va_arg(args, int);
	arg_type = ARG_TYPE(args_types, 1);
	value[0] = va_arg(args, int);
	if (arg_type == REG_CODE
		&& !get_reg_value(carriage, value[0], &value[0], PROC_ENDIAN))
		return (-1);
	else if (arg_type == IND_CODE)
	{
		value[0] = get_mem_value(env, carriage, value[0], true);
		swap_bytes(&value[0], sizeof(int));
	}
	arg_type = ARG_TYPE(args_types, 2);
	value[1] = va_arg(args, int);
	if (arg_type == REG_CODE
		&& !get_reg_value(carriage, value[1], &value[1], PROC_ENDIAN))
		return (-1);

	mempos = calc_mem_addr(carriage->position, value[0] + value[1], true);

	// ft_printf("mempos: %d, old val: %d\n",
	// 	mempos, *(int*)(env->field + mempos));
	// ft_printf("Register val: ");
	// print_memory(&carriage->registers[reg], 4);
	// ft_printf("\n");
	// ft_printf("Old memory val: ");
	// print_memory(env->field + mempos, 4);
	// ft_printf("\n");
	get_reg_value(carriage, reg, (int*)(env->field + mempos), BIG_END);
	// ft_printf("New memory val: ");
	// print_memory(env->field + mempos, 4);
	// ft_printf("\n");
	// ft_printf("reg val: %x, new mem val: %d\n",
	// 	carriage->registers[reg], *(int*)(env->field + mempos));
	// print_carriage(env, carriage);
	va_end(args);
	return (-1);
}
