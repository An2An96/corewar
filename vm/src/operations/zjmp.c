/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:16:16 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 12:02:08 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_zjmp(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	if (!carriage->carry)
		return (-1);
	VERB_LEVEL(SHOW_OPS) && write(1, " OK", 3);
	return (args[0].content);
}
