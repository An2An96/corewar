/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:17:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/21 16:00:42 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	get_reg_value(unsigned int *registers, unsigned char idx)
{
	return registers[idx];
}

int	op_sti(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned char	arg_type;
	unsigned char	reg;
	int	value1;
	int	value2;
	unsigned int	mempos;

	va_start(args, args_types);
	reg = va_arg(args, int);

	arg_type = ARG_TYPE(args_types, 1);
	value1 = va_arg(args, int);
	if (arg_type == T_REG)
		value1 = carriage->registers[value1];
	else if (arg_type == T_IND)
	{
		value1 = *((unsigned int*)(carriage->position + value1 % IDX_MOD));
		swap_bytes(&value1, sizeof(unsigned int));
	}

	arg_type = ARG_TYPE(args_types, 2);
	value2 = va_arg(args, int);
	(arg_type == T_REG) && (value2 = carriage->registers[value2]);
	ft_printf("op_sti, reg: %d, val1: %d, val2: %d\n", reg, value1, value2);
	ft_printf("%d + (%d + %d) %% %d | %d | %d\n", carriage->position, value1, value2, IDX_MOD, value1 + value2, (value1 + value2) % IDX_MOD);
	mempos = carriage->position + (value1 + value2) % IDX_MOD;
	
	ft_printf("mempos: %d, old val: %d\n", mempos, *(int*)(env->field + mempos));
	ft_printf("Register val: ");	print_memory(&carriage->registers[reg], 4);	ft_printf("\n");
	ft_printf("Old memory val: ");	print_memory(env->field + mempos, 4);		ft_printf("\n");
	*(int*)(env->field + mempos) = carriage->registers[reg];
	ft_printf("New memory val: ");	print_memory(env->field + mempos, 4);		ft_printf("\n");
	ft_printf("reg val: %x, new mem val: %d\n", carriage->registers[reg], *(int*)(env->field + mempos));
	// print_carriage(env, carriage);
	
	va_end(args);
	return (-1);
}
