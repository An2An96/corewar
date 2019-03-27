/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:13:09 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 12:02:35 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_live(t_env *env, t_carriage *carriage, int args_types, t_arg *args)
{
	int		player;
	int		i;

	player = args[0].content;
	carriage->last_live_cycle = env->acount_cycles;
	env->rcount_lives++;
	i = 0;
	while (env->champions[i])
	{
		if (i + 1 == -player)
		{
			env->last_live_champ = i;
			env->champions[i]->last_live_cycle = env->acount_cycles;
			if (VERB_LEVEL(SHOW_LIVES))
			{
				VERB_LEVEL(SHOW_OPS) && write(1, "\n", 1);
				ft_printf("Player %d (%s) is said to be alive",
					i + 1, env->champions[i]->prog_name);
				!VERB_LEVEL(SHOW_OPS) && write(1, "\n", 1);
			}
			break ;
		}
		i++;
	}
	return (-1);
}
