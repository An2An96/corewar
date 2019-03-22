/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:14:11 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 21:19:58 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		vm_check_die(t_env *env)
{
	ft_printf("vm_check_die %d\n", env->cycles_to_die);
	t_list		*cur_lst;
	t_carriage	*carriage;

	cur_lst = env->carriages;
	while (cur_lst)
	{
		carriage = (t_carriage*)cur_lst->content;
		if (env->cycles_to_die <= 0
			|| (env->acount_checks - carriage->last_live_cycle) >= env->cycles_to_die)
		{
			remove_carriage(&env->carriages, cur_lst);
		}
		cur_lst = cur_lst->next;
	}
	if (env->rcount_lives >= NBR_LIVE
		|| ++env->last_cycle_change_ctd == MAX_CHECKS)
	{
		env->cycles_to_die -= CYCLE_DELTA;
		env->last_cycle_change_ctd = 0;
	}
	env->rcount_lives = 0;
	env->acount_checks++;
	env->last_cycle_check = env->acount_cycles;
}

static void	vm_loop_helper(t_env *env)
{
	if (env->dump_nbr_cycle >= 0 && env->acount_cycles >= env->dump_nbr_cycle)
	{
		print_memory(env->field, MEM_SIZE);
		exit(EXIT_SUCCESS);
	}
	if (env->cycles_to_die <= 0
		|| (env->acount_cycles - env->last_cycle_check) == env->cycles_to_die)
	{
		vm_check_die(env);
	}
}

void		vm_loop(t_env *env)
{
	t_op		*op;
	t_list		*cur_lst;
	t_carriage	*carriage;

	vm_loop_helper(env);
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
		!carriage->cycles_to_execute
			&& do_op(env, carriage, env->field + carriage->position);
		cur_lst = cur_lst->next;
	}
	env->acount_cycles++;
	// ft_printf("cycle: %d\n", env->acount_cycles);
	vm_loop(env);
}
