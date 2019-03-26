/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:16:16 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/26 18:51:28 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_zjmp(t_env *env, t_carriage *carriage, int args_types, ...)
{
	va_list		args;
	int			new_pos;

	if (!carriage->carry)
		return (-1);
	va_start(args, args_types);
	new_pos = va_arg(args, int);
	VERB_LEVEL(SHOW_OPS) && write(1, " OK", 3);
	va_end(args);
	return (new_pos);
}
