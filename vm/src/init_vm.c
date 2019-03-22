/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:04:15 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/20 13:11:11 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_env(t_env *env)
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

	//	инициализация чемпиона
	i = 0;
	while (env->champions[i])
	{
		//	создание каретки
		SECURE_MALLOC(carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage)));
		carriage->position = offset * i;

		//	размещение исполняемого кода чемпиона
		ft_memcpy(env->field + carriage->position, env->champions[i]->exec_code, env->champions[i]->prog_size);

		carriage->registers[0] = -(i + 1);

		// print_carriage(env, carriage);

		ft_lstadd(&env->carriages, ft_lstnew_ptr(carriage));

		i++;
	}

	// print_memory(env->field, MEM_SIZE);
	
	env->cycles_to_die = CYCLE_TO_DIE;
}
