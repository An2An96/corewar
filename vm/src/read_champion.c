/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:21:12 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/20 15:21:59 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		read_exec_code(int fd, t_champion *champion)
{
	int				i;
	unsigned char	read_null;

	i = 0;
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
