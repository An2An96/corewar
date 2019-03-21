/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:26:57 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/21 16:08:50 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_ldi(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned char	arg_type;
	unsigned char	reg;
	int				value1;
	int				value2;
	unsigned int	mempos;

	va_start(args, args_types);
	
	arg_type = ARG_TYPE(args_types, 0);
	value1 = va_arg(args, int);
	if (arg_type == T_REG)
		value1 = carriage->registers[value1];
	else if (arg_type == T_IND)
	{
		value1 = *((unsigned int*)(carriage->position + value1 % IDX_MOD));
		swap_bytes(&value1, sizeof(unsigned int));
	}
	arg_type = ARG_TYPE(args_types, 1);
	value2 = va_arg(args, int);
	(arg_type == T_REG) && (value2 = carriage->registers[value2]);
	reg = va_arg(args, int);

	ft_printf("op_ldi, val1: %d, val2: %d, reg: %d\n", value1, value2, reg);

	ft_printf("%d + (%d + %d) %% %d | %d | %d\n", carriage->position, value1, value2, IDX_MOD, value1 + value2, (value1 + value2) % IDX_MOD);
	mempos = carriage->position + (value1 + value2) % IDX_MOD;
	
	ft_printf("mempos: %d, reg old val: %d\n", mempos, carriage->registers[reg]);
	
	ft_printf("Memory val: ");			print_memory(env->field + mempos, 4);		ft_printf("\n");
	ft_printf("Old register val: ");	print_memory(&carriage->registers[reg], 4);	ft_printf("\n");
	carriage->registers[reg] = *(int*)(env->field + mempos);
	ft_printf("New register val: ");	print_memory(&carriage->registers[reg], 4);		ft_printf("\n");
	
	ft_printf("new reg val: %d, mem val: %d\n", carriage->registers[reg], *(int*)(env->field + mempos));

	va_end(args);
	// exit(1);
	return (-1);
}
