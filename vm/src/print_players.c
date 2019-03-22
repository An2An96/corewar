/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:45:01 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/22 18:17:43 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_players(t_env *env)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (env->champions[i])
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1, env->champions[i]->prog_size, env->champions[i]->prog_name,
			env->champions[i]->comment);
		i++;
	}
}
