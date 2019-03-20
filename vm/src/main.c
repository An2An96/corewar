/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/20 15:23:49 by wballaba         ###   ########.fr       */
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

void	read_args(int argc, char **argv)
{
	int			i;
	t_list 		*listchamp;
	t_list		*new;
	t_champion	*champion;
	int			read_status;

	i = 1;
	read_status = 0;
	while (i < argc)
	{
		// if (read_status == 0)
		// {
		champion = read_champion(argv[i]);
		SECURE_MALLOC(new = ft_lstnew(champion, sizeof(t_champion)));
		ft_lstadd(&listchamp, new);
		print_champion((t_champion*)listchamp->content);
		// 	read_status++;
		// 	i++;
		// 	continue ;
		// }
		// champion = read_champion(argv[i]);
		// ft_lstpush(listchamp, champion);
		i++;
	}
}

int		main(int argc, char **argv)
{
	read_args(argc, argv);
	return (0);
}
