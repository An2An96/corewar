/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:20:09 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/28 20:23:25 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		cw_atoi(const char *str)
{
	int			i;
	long long	nb;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			throw_error(STR_ERROR_READ, "Invalid player nbr");
		nb = nb * 10 + (str[i] - '0');
		if (nb > 2147483647)
			throw_error(STR_ERROR_READ, "Invalid player nbr");
		i++;
	}
	return (nb);
}

void	put_champions_on_mask(int argc, char **argv, int *mask, int *i)
{
	int	nbr_player;

	nbr_player = 0;
	if (++(*i) < argc)
	{
		nbr_player = cw_atoi(argv[(*i)]);
		if (nbr_player - 1 < MAX_PLAYERS)
		{
			if (mask[nbr_player - 1] == 0)
				mask[nbr_player - 1] = 1;
			else
				throw_error(STR_ERROR_READ, "same player numbers");
		}
	}
	else
		throw_error(STR_ERROR_READ, "Invalid player nbr");
	if (++(*i) >= argc)
		throw_error(STR_ERROR_READ, "Invalid name file");
}

int		*create_mask(int argc, char **argv)
{
	int	*mask;
	int i;

	i = 1;
	SECURE_MALLOC(mask = (int*)ft_memalloc(sizeof(int) * MAX_PLAYERS));
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			put_champions_on_mask(argc, argv, mask, &i);
			continue ;
		}
		i++;
	}
	return (mask);
}

int		read_flags(int argc, char **argv, t_env *env, int *i)
{
	int	nbr_player;

	nbr_player = 0;
	if (!ft_strcmp(argv[(*i)], "-dump") && ++(*i) < argc)
		env->dump_nbr_cycle = cw_atoi(argv[(*i)]);
	else if (!ft_strcmp(argv[(*i)], "-n"))
	{
		if (++(*i) < argc)
			nbr_player = cw_atoi(argv[(*i)]);
		if (nbr_player > MAX_PLAYERS || nbr_player == 0)
			throw_error(STR_ERROR_READ, "Invalid player nbr");
		(*i)++;
		return (nbr_player);
	}
	else if (!ft_strcmp(argv[(*i)], "-v"))
	{
		if (++(*i) < argc)
			env->verb_levels = cw_atoi(argv[(*i)]);
	}
	else if (!ft_strcmp(argv[(*i)], "-nv"))
		env->use_ncurses = true;
	else
		return (0);
	return (-1);
}

void	read_args(int argc, char **argv, t_env *env)
{
	int			i;
	t_champion	*champion;
	int			nbr_player;
	int			count_champion;
	int			*mask;

	if (argc == 1)
		throw_error(STR_ERROR_READ, "Invalid name file");
	count_champion = 0;
	SECURE_MALLOC(env->champions = (t_champion**)
		ft_memalloc(sizeof(t_champion*) * (MAX_PLAYERS + 1)));
	mask = create_mask(argc, argv);
	env->dump_nbr_cycle = -1;
	i = 0;
	while (++i < argc)
	{
		if (count_champion > MAX_PLAYERS)
			throw_error(STR_ERROR_READ, "Incorrect count players");
		if ((nbr_player = read_flags(argc, argv, env, &i)) == -1)
			continue ;
		put_champ_on_arr(nbr_player, argv[i], env, mask);
		count_champion++;
	}
	check_arr_champions(count_champion, mask, env);
	free(mask);
}
