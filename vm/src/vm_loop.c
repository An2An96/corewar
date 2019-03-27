/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:14:11 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 15:32:26 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	vm_end(t_env *env)
{
	int8_t winner;

	winner = env->last_live_champ;
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner + 1, env->champions[winner]->prog_name);
	return (0);
}

int			vm_check_die(t_env *env)
{
	t_list		*cur_lst;
	t_carriage	*carriage;

	if (env->cycles_to_die <= 0
		|| (env->acount_cycles - env->last_cycle_check) == env->cycles_to_die)
	{
		cur_lst = env->carriages;
		while (cur_lst)
		{
			carriage = (t_carriage*)cur_lst->content;
			if (env->cycles_to_die <= 0
				|| carriage->last_live_cycle <= env->last_cycle_check)
			{
				VERB_LEVEL(SHOW_DEATHS) &&
					ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					carriage->id,
					env->acount_cycles - carriage->last_live_cycle,
					env->cycles_to_die);
				cur_lst = remove_carriage(env, cur_lst);
				if (!env->carriages_count)
					return (vm_end(env));
				else
					continue;
			}
			cur_lst = cur_lst->next;
		}
		if (env->rcount_lives >= NBR_LIVE
			|| ++env->last_cycle_change_ctd == MAX_CHECKS)
		{
			env->cycles_to_die -= CYCLE_DELTA;
			env->last_cycle_change_ctd = 0;
			VERB_LEVEL(SHOW_CYCLES) &&
				ft_printf("Cycle to die is now %d\n", env->cycles_to_die);
		}
		env->rcount_lives = 0;
		env->acount_checks++;
		env->last_cycle_check = env->acount_cycles;
	}
	return (1);
}

void		vm_loop(t_env *env)
{
	t_op		*op;
	t_list		*cur_lst;
	t_carriage	*carriage;

	env->acount_cycles++;
	if (env->dump_nbr_cycle >= 0 && env->acount_cycles > env->dump_nbr_cycle)
	{
		print_memory(env->field, MEM_SIZE);
		exit(EXIT_SUCCESS);
	}
	VERB_LEVEL(SHOW_CYCLES)
		&& ft_printf("It is now cycle %d\n", env->acount_cycles);
	cur_lst = env->carriages;
	while (cur_lst)
	{
		carriage = (t_carriage*)cur_lst->content;
		if (!carriage->cycles_to_execute)
		{
			carriage->op_code = env->field[carriage->position];
			(op = get_op(carriage->op_code))
				&& (carriage->cycles_to_execute = op->cycles_to_execute);
		}
		carriage->cycles_to_execute && --carriage->cycles_to_execute;
		if (carriage->cycles_to_execute == 0)
		{
			carriage->position =
				do_op(env, carriage, env->field + carriage->position);
		}
		cur_lst = cur_lst->next;
	}
}
