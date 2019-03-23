/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:23:38 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/22 15:59:45 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

int         ft_count_lines(char *str)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            count++;
        i++;
    }
    return (count);
}

static int  ft_find_char_pos(char *str, char c, int pos)
{
    int i;
    int len;

    len = (int)ft_strlen(str);
    if (pos >= len)
        return (len);
    i = pos;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (i);
}

static void ft_make_lines_split(char **res, char *str, int count)
{
    int     i;
    int     start;
    int     pos;
    char    *tmp;

    start = 0;
    i = 0;
    tmp = NULL;
    while (i < count)
    {
        pos = ft_find_char_pos(str, '\n', start);
        tmp = ft_strsub(str, (unsigned int)start, (unsigned int)pos - start);
        res[i] = tmp;
        start = pos + 1;
        i++;
    }
}

char        **ft_lines_split(char *str)
{
    char    **res;
    int     count;

    count = ft_count_lines(str);
    res = (char **)malloc(sizeof(char *) * count + 1);
    CHECK_NULL(res);
    ft_make_lines_split(res, str, count);
    res[count] = 0;
    return (res);
}