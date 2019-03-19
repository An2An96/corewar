/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:59:07 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/19 20:18:39 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// void print_champion()

int	main(int argc, char **argv)
{
	int magic_header;
	int	fd;
	t_champion *champion;
	unsigned int buf;

	fd = open(argv[1], O_RDONLY);

	read(fd, &magic_header, sizeof(int));
	swap_bytes(&magic_header, sizeof(magic_header));
	if (magic_header != COREWAR_EXEC_MAGIC)
		throw_error("[Validation Error]:", "error magic header");
	SECURE_MALLOC(champion = (t_champion*)malloc(sizeof(t_champion)));
	read(fd, &champion->prog_name, PROG_NAME_LENGTH);
	champion->prog_name[PROG_NAME_LENGTH] = '\0';
	read(fd, &buf, sizeof(buf));
	if (buf)
		throw_error("[Validation Error]:", "error NULL 1");
	read(fd, &champion->prog_size, sizeof(int));
	read(fd, &champion->comment, COMMENT_LENGTH);
	champion->comment[COMMENT_LENGTH] = '\0';
	read(fd, &buf, sizeof(buf));
	if (buf)
		throw_error("[Validation Error]:", "error NULL 2");
	ft_printf("Champ:\nName: %s\nComment: %s\n", champion->prog_name, champion->comment);

	return (0);
}
