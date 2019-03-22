/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:16:16 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/21 14:29:06 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_zjmp(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned int	offset;
	int				new_pos;

	ft_printf("op_zjmp");
	if (carriage->carry)
	{
		va_start(args, args_types);
		offset = va_arg(args, int);
		new_pos = carriage->position + offset % IDX_MOD;
		ft_printf(", offset: %d\n", offset);
		print_carriage(env, carriage);
		va_end(args);
	}
	ft_printf("\n");
	return (new_pos);
}
