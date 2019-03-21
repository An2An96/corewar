/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:21:12 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/21 17:52:40 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		read_exec_code(int fd, t_champion *champion)
{
	int				i;
	unsigned char	read_null;

	i = 0;
    // if (champion->prog_size > CHAMP_MAX_SIZE)
    //     throw_error("[Validation Error]:",
    //         "error exec code champion more than CHAMP_MAX_SIZE");
	SECURE_MALLOC(champion->exec_code = (unsigned char*)
		ft_memalloc(sizeof(unsigned char) * champion->prog_size));
	while (i < champion->prog_size)
	{
		if (read(fd, champion->exec_code, 1) == 0)
			throw_error("[Validation Error]:", "error exec code");
		champion->exec_code++;
		i++;
	}
	if (read(fd, &read_null, sizeof(read_null)))
		throw_error("[Validation Error]:", "error size exec code");
	champion->exec_code -= champion->prog_size;
}

t_champion	*read_champion(char *filename)
{
	int				magic_header;
	t_champion		*champion;
	unsigned int	read_null;
	int				fd;

	fd = open(filename, O_RDONLY);
	read(fd, &magic_header, sizeof(int));
	swap_bytes(&magic_header, sizeof(magic_header));
	if (magic_header != COREWAR_EXEC_MAGIC)
		throw_error("[Validation Error]:", "error magic header");
	SECURE_MALLOC(champion = (t_champion*)malloc(sizeof(t_champion)));
	read(fd, &champion->prog_name, PROG_NAME_LENGTH);
	champion->prog_name[PROG_NAME_LENGTH] = '\0';
	read(fd, &read_null, sizeof(read_null));
	if (read_null)
		throw_error("[Validation Error]:", "error NULL 1");
	read(fd, &champion->prog_size, sizeof(champion->prog_size));
	swap_bytes(&champion->prog_size, sizeof(champion->prog_size));
	read(fd, &champion->comment, COMMENT_LENGTH);
	champion->comment[COMMENT_LENGTH] = '\0';
	read(fd, &read_null, sizeof(read_null));
	if (read_null)
		throw_error("[Validation Error]:", "error NULL 2");
	read_exec_code(fd, champion);
	return (champion);
}

int			cw_atoi(const char *str)
{
	int			i;
	long long	nb;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			throw_error("[Read Error]:", "Invalid player nbr");
		nb = nb * 10 + (str[i] - '0');
		if (nb > 2147483647)
			throw_error("[Read Error]:", "Invalid player nbr");
		i++;
	}
	if (nb > MAX_PLAYERS || nb == 0)
		throw_error("[Read Error]:", "Invalid player nbr");
	return (nb);
}

int		*create_mask(int argc, char **argv)
{
	int	*mask;
	int i;
	int	nbr_player;

	i = 0;
	nbr_player = 0;
	SECURE_MALLOC(mask = (int*)ft_memalloc(sizeof(int) * MAX_PLAYERS));
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			if (++i < argc)
			{
				nbr_player = cw_atoi(argv[i]);
				if (nbr_player - 1 < MAX_PLAYERS)
				{
					if (mask[nbr_player - 1] == 0)
						mask[nbr_player - 1] = 1;
					else
						throw_error("[Read Error]:", "same player numbers");
				}
			}
			else
				throw_error("[Read Error]:", "Invalid player nbr");
			if (++i >= argc)
				throw_error("[Read Error]:", "Invalid name file");
			continue ;
		}
		i++;
	}
	return (mask);
}

void read_args(int argc, char **argv, t_env *env)
{
	int			i;
	t_champion	*champion;
	int			nbr_player;
	int			count_champion;
	int			*mask;
	int			j;

	if (argc == 1)
		throw_error("[Read Error]:", "Invalid name file");
	i = 1;

	nbr_player = 0;
	count_champion = 0;
	SECURE_MALLOC(env->champions = (t_champion**)ft_memalloc(sizeof(t_champion*) * (MAX_PLAYERS + 1)));
	mask = create_mask(argc, argv);
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-dump"))
		{
			if (++i < argc)
				env->dump_nbr_cycle = cw_atoi(argv[i]);
			i++;
			ft_printf("get dump = %d\n", env->dump_nbr_cycle );
		}
		if (count_champion > MAX_PLAYERS)
			throw_error("[Read Error]:", "Incorrect count players");
		nbr_player = 0;
		if (!ft_strcmp(argv[i], "-n"))
		{
			if (++i < argc)
				nbr_player = cw_atoi(argv[i]);
			i++;
		}
		if (nbr_player)
			env->champions[nbr_player - 1] = read_champion(argv[i]);
		else
		{
			j = 0;
			while (mask[j] != 0)
				j++;
			mask[j] = 1;
			env->champions[j] = read_champion(argv[i]);
		}
		count_champion++;
		i++;
	}
	if (count_champion > MAX_PLAYERS)
		throw_error("[Read Error]:", "Incorrect count players");
	j = 0;
	while (j < count_champion)
	{
		if (mask[j] == 0)
			throw_error("[Read Error]:", "Incorrect position players");
		j++;
	}
	j = 0;
	ft_printf("ANTON HUI\n");
	while (j < count_champion)
	{
		print_champion(env->champions[j]);
		j++;
	}
}
