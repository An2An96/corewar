/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/28 20:29:09 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	t_champion	**champions;
	t_env		*env;

	SECURE_MALLOC(env = ft_memalloc(sizeof(t_env)));
	read_args(argc, argv, env);
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
	return (0);
}
