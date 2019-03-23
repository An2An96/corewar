/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:36 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 17:14:24 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lines  *ft_create_lines(char *str)
{
    t_lines *res;
    char    **lines;
    int     count;

    res = (t_lines *)malloc(sizeof(t_lines));
    CHECK_NULL(res);
    res->count = ft_count_lines(str);
    res->line = ft_lines_split(str);
    return (res);
}

static char     *ft_read_file(int fd)
{
    char    buffer[BUFF + 1];
    char    *res;
    int     ret;

    res = NULL;
    if (read(fd, buffer, 0) < 0) {
        perror("read");
        exit(1);
    }
    while ((ret = (int)read(fd, buffer, BUFF)) > 0)
    {
        buffer[ret] = '\0';
        ft_str_extend(&res, buffer);
    }
    return (res);
}

int             main(int argc, char *argv[])
{
    int         fd;
    t_lines     *lines;
    char        *buff;
    t_tokens    *tokens;

    if (argc < 2)
    {
        ft_putendl("Usage: Enter name of the .s file containing your champion");
        exit(0);
    }
    else if (argc > 2)
    {
        ft_putendl("I can interpret only one champion at the time");
        exit(0);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    if (ft_file_name_validity(argv[1]) == false)
        exit(1);
    buff = ft_read_file(fd);
    if (buff == NULL)
    {
        ft_putendl("There are no information at all about champion in the file!");
        exit(1);
    }
    lines = ft_create_lines(buff);
    tokens = ft_get_tokens(lines);
    ft_strdel(&buff);
    // TODO: function to delete lines structure
    close(fd);
    exit(0);
}