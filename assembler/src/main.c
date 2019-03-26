/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:36 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/26 16:03:12 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void            ft_expand_lines(t_lines **lines, char *line)
{
    int     i;
    char    *new;
    int     len;
    int     count;

    new = ft_strdup(line);
	count = (*lines)->count + 1;
    (*lines)->line = realloc((*lines)->line, sizeof(char *) * count);
	(*lines)->count = count;
    (*lines)->line[count - 1] = new;
}

static t_lines  *ft_read_file(int fd, char **line)
{
    t_lines *lines;

    lines = (t_lines *)ft_memalloc(sizeof(t_lines));
	CHECK_NULL(lines);
    while (get_next_line(fd, line) > 0)
        ft_expand_lines(&lines, *line);
    return (lines);
}

int             main(int argc, char *argv[])
{
    int         fd;
    t_lines     *lines;
    t_tokens    *tokens;
    char        *line;
    t_lexical_err   *lex_errors;

    line = NULL;
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
    lines = ft_read_file(fd, &line);
    if (lines->count == 0)
    {
        ft_putendl("There are no information at all about champion in the file!");
        exit(1);
    }
    tokens = ft_get_tokens(lines);
    lex_errors = NULL;
    lex_errors = ft_get_lex_errors(tokens);
    if (lex_errors)
    {
		print_errors(argv[1], lex_errors);
		exit(1);
	}
	delete_str_commas(tokens);
    // TODO: function to delete lex_errors
    // TODO: function to delete tokens structure
    // TODO: function to delete lines structure
    close(fd);
    exit(0);
}
