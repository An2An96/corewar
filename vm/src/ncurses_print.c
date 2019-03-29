/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:51:14 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 11:06:44 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					ncurses_init(void)
{
	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_RED);
	return (1);
}

int					ncurses_destroy(void)
{
	getch();
	endwin();
	return (1);
}

inline static char	get_hex_char(char octet)
{
	return ((octet < 10 ? '0' : ('a' - 10)) + octet);
}

int					ncurses_print_env(t_env *env)
{
	int		i;

	clear();
	i = 0;
	while (i < MEM_SIZE)
	{
		addch(' ');
		addch(get_hex_char(env->field[i] >> 4));
		addch(get_hex_char(env->field[i] & 0xF));
		i++;
		if (i % 64 == 0)
			addch('\n');
	}
	refresh();
	getch();
	return (1);
}
