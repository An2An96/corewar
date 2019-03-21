/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 13:14:11 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/21 16:18:48 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"	

t_op_func	g_op_funcs[] = {
	NULL,
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};

t_op	*get_op(char op_code)
{
	int8_t i;

	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (g_op_tab[i].op_code == op_code)
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
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

void	check_die(t_env *env)
{
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

unsigned int	get_arg(char type, bool dir_ind_size, unsigned char **mempos)
{
	unsigned int arg;

	if (type == REG_CODE)
	{
		// print_memory(*mempos, 1);	ft_printf("\n");
		arg = *((unsigned char*)(*mempos));
		swap_bytes(&arg, sizeof(unsigned char));
		*mempos += sizeof(unsigned char);
	}
	else if (type == IND_CODE || dir_ind_size)
	{
		// print_memory(*mempos, 2);	ft_printf("\n");
		arg = *((unsigned short*)(*mempos));
		swap_bytes(&arg, sizeof(unsigned short));
		*mempos += sizeof(unsigned short);
	}
	else if (type == DIR_CODE)
	{
		// print_memory(*mempos, 4);	ft_printf("\n");
		arg = *((unsigned int*)(*mempos));
		swap_bytes(&arg, sizeof(unsigned int));
		*mempos += sizeof(unsigned int);
	}
	return (arg);
}

unsigned char	*do_op(t_env *env, t_carriage *carriage, unsigned char *mempos)
{
	t_op			*op;
	int	args[3];
	// unsigned char	arg_type[3];
	unsigned char	args_types;
	bool			invalid_args;
	int				new_pos;

	// print_memory(mempos, 1);	ft_printf("\n");
	op = get_op(carriage->op_code);
	if (op->codage_octal)
	{
		args_types = *mempos;
		// arg_type[0] = ARG_TYPE(*mempos, 0); //(*mempos) >> 6;
		// arg_type[1] = ARG_TYPE(*mempos, 1); //(*mempos) >> 4 & 0x3;
		// arg_type[2] = ARG_TYPE(*mempos, 2); //(*mempos) >> 2 & 0x3;
		invalid_args = (!(ARG_TYPE(args_types, 0) & op->arg_type[0]
			&& (op->arg_count < 2 || ARG_TYPE(args_types, 1) & op->arg_type[1])
			&& (op->arg_count < 3 || ARG_TYPE(args_types, 2) & op->arg_type[2])));
		mempos++;
	}
	else
		args_types = T_DIR << 6;
		// arg_type[0] = T_DIR;
	args[0] = get_arg(ARG_TYPE(args_types, 0), op->dir_ind_size, &mempos);
	if (op->arg_count > 1)
		args[1] = get_arg(ARG_TYPE(args_types, 1), op->dir_ind_size, &mempos);
	if (op->arg_count > 2)
		args[2] = get_arg(ARG_TYPE(args_types, 2), op->dir_ind_size, &mempos);
	// ft_printf("args: %d %d %d\n", args[0], args[1], args[2]);
	if (!invalid_args)
	{
		if (op->arg_count == 1)
			new_pos = g_op_funcs[carriage->op_code](env, carriage, args_types, args[0]);
		else if (op->arg_count == 2)
			new_pos = g_op_funcs[carriage->op_code](env, carriage, args_types, args[0], args[1]);
		else if (op->arg_count == 3)
			new_pos = g_op_funcs[carriage->op_code](env, carriage, args_types, args[0], args[1], args[2]);
	}
	else	//	for debug
	{
		new_pos = -1;
		ft_printf("invalid arg types\n");
	}
	carriage->position = (new_pos != -1) ? new_pos : mempos - env->field;
	ft_printf("[!] new carriage pos: %d | ", carriage->position);
	print_memory(env->field + carriage->position, 1);
	ft_printf("\n\n");
	return (mempos);
}

void	vm_loop(t_env *env)
{
	t_list		*cur_lst;
	t_carriage	*carriage;
	
	if (env->cycles_to_die <= 0
		|| (env->acount_cycles - env->last_cycle_check) == env->cycles_to_die)
	{
		check_die(env);
	}

	cur_lst = env->carriages;
	while (cur_lst)
	{
		carriage = (t_carriage*)cur_lst->content;
		if (carriage->cycles_to_execute)
		{
			if (--carriage->cycles_to_execute == 0)
			{
				if (env->field[carriage->position]
					&& env->field[carriage->position] <= 0x10)
				{
					// ft_printf("do_op: start: %d, pos: %d = %d\n", env->field, carriage->position, env->field + carriage->position);
					do_op(env, carriage, env->field + carriage->position + 1);
				}
				else
					carriage->position++;
			}
		}
		else
		{
			carriage->op_code = env->field[carriage->position];
			// ft_printf("new op_code: %d\n", carriage->op_code);
			if (env->field[carriage->position]
				&& env->field[carriage->position] <= 0x10)
			{
				carriage->cycles_to_execute =
					get_op(carriage->op_code)->cycles_to_execute;
				// ft_printf("new op_code: %d [cycles to execute: %d]\n", carriage->op_code, carriage->cycles_to_execute);
			}
			// else
			// 	carriage->position++;
		}
		cur_lst = cur_lst->next;
	}
	env->acount_cycles++;
	vm_loop(env);
}
