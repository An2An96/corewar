/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:04:15 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/19 20:19:35 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_env	*init_vm(t_list *champions)
{
	int8_t		i;
	int8_t		j;
	int			offset;
	int8_t		champions_count;
	t_env		*vm;
	t_list		*cur_lst;
	t_champion	*cur_champ;
	t_carriage	*carriage;

	SECURE_MALLOC(vm = ft_memalloc(sizeof(t_env)));
	champions_count = ft_lstlen(champions);
	offset = MEM_SIZE / champions_count;

	//	инициализация чемпиона
	i = 0;
	cur_lst = champions;
	while (champions)
	{
		cur_champ = (t_champion*)cur_lst->content;
		
		//	создание каретки
		SECURE_MALLOC(carriage = ft_memalloc(sizeof(t_carriage)));
		carriage->position = offset * i;

		//	размещение исполняемого кода чемпиона
		ft_memcpy(vm->field + carriage->position, cur_champ->exec_code, cur_champ->prog_size);

		j = 0;
		while (j < REG_NUMBER)
			SECURE_MALLOC(carriage->registers[j++] = ft_memalloc(REG_SIZE));
		// carriage->registers[0] = -(i + 1);

		ft_lstadd(&vm->carriages, ft_lstnew(carriage, sizeof(carriage)));

		cur_lst = cur_lst->next;
		i++;
	}

	print_memory(vm->field, MEM_SIZE);
	
	vm->cycles_to_die = CYCLE_TO_DIE;
	return (vm);
}
