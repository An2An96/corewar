/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/20 17:07:06 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_champion(t_champion *champion)
{
	ft_printf("\nChamp:\nName: %s\nComment: %s\nSize exec: %u\n",
		champion->prog_name, champion->comment, champion->prog_size);
	print_memory(champion->exec_code, champion->prog_size);
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	read_args(argc, argv);
	return (0);
}
