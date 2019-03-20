/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/20 16:56:37 by rschuppe         ###   ########.fr       */
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

t_list	*read_args(int argc, char **argv)
{
	int			i;
	t_list 		*listchamp;
	t_list		*new;
	t_champion	*champion;
	int			read_status;

	i = 1;
	read_status = 0;
	listchamp = NULL;
	while (i < argc)
	{
		champion = read_champion(argv[i]);
		SECURE_MALLOC(new = ft_lstnew(champion, sizeof(t_champion)));
		ft_lstadd(&listchamp, new);
		// print_champion((t_champion*)listchamp->content);
		i++;
	}
	return (listchamp);
}

int		main(int argc, char **argv)
{
	t_list	*champions;
	t_env	*env;

	champions = read_args(argc, argv);
	env = init_env(champions);
	vm_loop(env);
	return (0);
}
