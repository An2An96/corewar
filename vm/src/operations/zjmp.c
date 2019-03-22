/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:16:16 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 15:27:29 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_zjmp(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list			args;
	unsigned int	offset;
	int				new_pos;

	if (!carriage->carry)
		return (-1);
	va_start(args, args_types);
	offset = va_arg(args, int);
	new_pos = carriage->position + offset % IDX_MOD;
	print_carriage(env, carriage);
	va_end(args);
	return (new_pos);
}
