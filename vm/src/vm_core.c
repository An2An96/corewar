/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:50:41 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 08:58:51 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_init(t_env *env)
{
	int8_t		i;
	int8_t		j;
	int			offset;
	int8_t		champions_count;
	t_carriage	*carriage;

	i = 0;
	while (env->champions[i])
		i++;
	champions_count = i;
	offset = MEM_SIZE / champions_count;
	i = 0;
	while (env->champions[i])
	{
		carriage = create_carriage(env, NULL, offset * i);
		carriage->registers[0] = -(i + 1);
		if (DIFF_ENDIAN)
			swap_bytes(&carriage->registers[0], sizeof(carriage->registers[0]));
		ft_memcpy(env->field + carriage->position,
			env->champions[i]->exec_code, env->champions[i]->prog_size);
		i++;
	}
	env->cycles_to_die = CYCLE_TO_DIE;
	print_players(env);
}

void	vm_destroy(t_env *env)
{
	int i;

	i = 0;
	while (env->champions[i])
	{
		free(env->champions[i]->exec_code);
		free(env->champions[i]);
		i++;
	}
	free(env->champions);
	free(env);
}
