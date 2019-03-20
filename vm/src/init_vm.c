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

t_env	*init_env(t_list *champions)
{
	int8_t		i;
	int8_t		j;
	int			offset;
	int8_t		champions_count;
	t_env		*env;
	t_list		*cur_lst;
	t_champion	*cur_champ;
	t_carriage	*carriage;

	// ft_printf("exec code of champion:\n");
	// print_memory(((t_champion*)champions->content)->exec_code, ((t_champion*)champions->content)->prog_size);
	// ft_printf("\n\n");
	SECURE_MALLOC(env = ft_memalloc(sizeof(t_env)));
	champions_count = ft_lstlen(champions);
	offset = MEM_SIZE / champions_count;

	//	инициализация чемпиона
	i = 0;
	cur_lst = champions;
	while (cur_lst)
	{
		cur_champ = (t_champion*)cur_lst->content;
		
		//	создание каретки
		SECURE_MALLOC(carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage)));
		carriage->position = offset * i;

		//	размещение исполняемого кода чемпиона
		ft_memcpy(env->field + carriage->position, cur_champ->exec_code, cur_champ->prog_size);

		carriage->registers[0] = -(i + 1);

		print_carriage(env, carriage);

		ft_lstadd(&env->carriages, ft_lstnew_ptr(carriage));

		cur_lst = cur_lst->next;
		i++;
	}

	print_memory(env->field, MEM_SIZE);
	
	env->cycles_to_die = CYCLE_TO_DIE;
	return (env);
}
