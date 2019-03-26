/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:39:46 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 21:34:47 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

static char *ft_str_create(char const *new)
{
    int     len;
    int     i;
    char    *res;

    len = 0;
    i = 0;
    res = NULL;
    if (new == NULL)
        return (NULL);
    len = (int)ft_strlen(new);
    res = (char *)malloc(sizeof(char) * len + 1);
    CHECK_NULL(res);
    while (new[i])
    {
        res[i] = new[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

void        ft_str_extend(char **str, char const *new)
{
    int     len;
    char    *tmp;

    len = 0;
    tmp = NULL;
    if (new == NULL)
        return ;
    len = (int)ft_strlen(new);
    if (len == 0)
        return ;
    if (*str == NULL)
        *str = ft_str_create(new);
    else
    {
        tmp = ft_strjoin(*str, new);
        ft_strdel(str);
        *str = tmp;
    }
}

t_bool		ft_is_label_char(char c)
{
	int i;

	i = 0;
	while(LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (true);
		i++;
	}
	return (false);
}

t_bool		ft_is_undefined(char c)
{
	if (ft_isdigit(c))
		return (false);
	else if (ft_isalpha_small(c))
		return (false);
	else if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR || c == LABEL_CHAR ||
			c == DIRECT_CHAR || c == SEPARATOR_CHAR)
		return (false);
	else if (c == '"' || c == '.')
		return (false);
	else if (ft_is_label_char(c) == true)
		return (false);
	return (true);
}

t_bool		ft_is_digit_sign(char c)
{
	if (c == '-')
		return (true);
	if (c == '+')
		return (true);
	return (false);
}