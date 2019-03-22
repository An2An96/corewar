/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:21:14 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 18:22:29 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage	*create_carriage(t_env *env, t_carriage *parent, unsigned int pos)
{
	t_carriage *new_carriage;

	SECURE_MALLOC(new_carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage)));
	ft_lstadd(&env->carriages, ft_lstnew_ptr(new_carriage));
	if (parent)
	{
		ft_printf("PARENT:\n");
		print_carriage(env, parent);

		ft_memcpy(new_carriage->registers,
			parent->registers, REG_NUMBER * sizeof(unsigned int));
		new_carriage->carry = parent->carry;
		new_carriage->last_live_cycle = parent->last_live_cycle;
	}
	new_carriage->position = pos;
	ft_printf("NEW CARRIAGE:\n");
	print_carriage(env, new_carriage);
	return (new_carriage);
}

void	remove_carriage(t_list **carriages, t_list *die_carriage)
{
	t_list	*cur_lst;

	if (*carriages == die_carriage)
	{
		*carriages = (*carriages)->next;
		free(die_carriage);
		return ;
	}
	cur_lst = *carriages;
	while (cur_lst && cur_lst->next)
	{
		if (cur_lst->next == die_carriage)
		{
			cur_lst->next = die_carriage->next;
			free(die_carriage);
		}
		cur_lst = cur_lst->next;
	}
}

void	set_carriage_pos(t_carriage *carriage, int pos)
{
	pos %= MEM_SIZE;
	(pos < 0) && (pos = MEM_SIZE - pos);
	carriage->position = pos;

	ft_printf("[!] new carriage pos: %d\n\n", carriage->position);
}
