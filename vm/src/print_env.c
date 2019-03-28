/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:51:14 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/28 20:51:41 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

inline static char	get_hex_char(char octet)
{
	return ((octet < 10 ? '0' : ('a' - 10)) + octet);
}

int					print_env(t_env *env)
{
	int		i;
	chtype	ch;

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
