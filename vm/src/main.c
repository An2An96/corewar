/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/25 19:34:00 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	t_champion	**champions;
	t_env		*env;

	SECURE_MALLOC(env = ft_memalloc(sizeof(t_env)));
	// initscr();
	// printw("Hello world!\n");  // Отображение приветствия в буфер
    // refresh();                   // Вывод приветствия на настоящий экран
    // getch();                     // Ожидание нажатия какой-либо клавиши пользователем
    // endwin();
	read_args(argc, argv, env);
	init_env(env);
	while (vm_check_die(env))
		vm_loop(env);
	return (0);
}
