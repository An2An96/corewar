/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 09:27:07 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	t_champion	**champions;
	t_env		*env;

	SECURE_MALLOC(env = ft_memalloc(sizeof(t_env)));
	if (read_args(argc, argv, env))
	{
		if (env->use_ncurses)
		{
			initscr();
			start_color();
			init_pair(1, COLOR_BLUE, COLOR_RED);
		}
		vm_init(env);
		while (vm_check_die(env))
		{
			env->use_ncurses && print_env(env);
			vm_loop(env);
			env->use_ncurses && usleep(10000);
		}
		vm_destroy(env);
		if (env->use_ncurses)
		{
			getch();
			endwin();
		}
	}
	else
	{
		ft_printf(COLOR_USAGE "Usage: " COLOR_NONE
			"./corewar [-dump N -v N] <champion1.cor> <...>\n");
		ft_printf("\t%-10s : "
			"Dumps memory after N cycles then exits\n", "-dump N");
		ft_printf("\t%-10s : "
			"Verbosity levels, can be added together to enable several\n",
			"-v N");
		ft_printf("%20s : Show only essentials\n", "- 0");
		ft_printf("%20s : Show lives\n", "- 1");
		ft_printf("%20s : Show cycles\n", "- 2");
		ft_printf("%20s : "
			"Show operations (Params are NOT litteral ...)\n", "- 4");
		ft_printf("%20s : Show deaths\n", "- 8");
		ft_printf("%20s : Show PC movements (Except for jumps)\n", "- 16");
	}
	return (0);
}
