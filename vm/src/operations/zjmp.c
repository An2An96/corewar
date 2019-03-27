/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:16:16 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 19:31:38 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_zjmp(t_env *env, t_carriage *carriage, t_arg *args)
{
	if (VERB_LEVEL(SHOW_OPS))
		ft_printf("P%5d | zjmp %d %s\n",
			carriage->id, args[0].content, carriage->carry ? "OK" : "FAILED");
	return (carriage->carry ? args[0].content : -1);
}
