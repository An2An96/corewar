/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:25:58 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/28 20:25:59 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage	*create_carriage(t_env *env, t_carriage *parent, unsigned int pos)
{
	t_carriage *new_carriage;

	SECURE_MALLOC(new_carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage)));
	ft_lstadd(&env->carriages, ft_lstnew_ptr(new_carriage));
	new_carriage->id = ++env->last_carriage_id;
	if (parent)
	{
		ft_memcpy(new_carriage->registers,
			parent->registers, REG_NUMBER * sizeof(unsigned int));
		new_carriage->carry = parent->carry;
		new_carriage->last_live_cycle = parent->last_live_cycle;
	}
	new_carriage->position = pos;
	env->carriages_count++;
	return (new_carriage);
}

t_list *remove_carriage(t_env *env, t_list *die_carriage)
{
	t_list	*cur_lst;
	t_list	*next;

	next = die_carriage->next;
	if (env->carriages == die_carriage)
		env->carriages = env->carriages->next;
	else
	{
		cur_lst = env->carriages;
		while (cur_lst && cur_lst->next)
		{
			if (cur_lst->next == die_carriage)
			{
				cur_lst->next = die_carriage->next;
				break ;
			}
			cur_lst = cur_lst->next;
		}
	}
	free(die_carriage->content);
	free(die_carriage);
	env->carriages_count--;
	return (next);
}

void	set_carriage_pos(t_env *env, t_carriage *carriage, int pos)
{
	pos %= MEM_SIZE;
	(pos < 0) && (pos = MEM_SIZE - pos);
	carriage->position = pos;
}
