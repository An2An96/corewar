/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_lexems.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:50:36 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/25 18:26:57 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

t_lexem   *ft_get_command(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = cur->pos + 1;
	while (str[j])
	{
		if (!ft_isalpha_small(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = COMMAND;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_string(t_lines *lines, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;
	char        *tmp;
	char 		*ans;
	char		*new;
	int 		flag;

	res = NULL;
	tmp = NULL;
	ans = ft_strnew(0);
	flag = false;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = cur->pos + 1;
	res->start = cur->pos;
	res->line = cur->line;
	while (cur->line < lines->count)
	{
		while (1)
		{
			if (lines->line[cur->line][j] == '\0')
			{
				len = j - cur->pos;
				tmp = ft_strsub(lines->line[cur->line], (unsigned int)cur->pos, (unsigned int)len);
				new = ft_strjoin(ans, tmp);
				ft_strdel(&ans);
				ans = new;
				ft_strdel(&tmp);
				break ;
			}
			if (lines->line[cur->line][j] == '"')
			{
				len = j - cur->pos + 1;
				tmp = ft_strsub(lines->line[cur->line], (unsigned int)cur->pos, (unsigned int)len);
				new = ft_strjoin(ans, tmp);
				ft_strdel(&ans);
				ans = new;
				ft_strdel(&tmp);
				cur->pos = j + 1;
				flag = true;
				break ;
			}
			j++;
		}
		if (flag == true)
			break ;
		j = 0;
		cur->pos = 0;
		cur->line++;
	}
	res->value = ans;
	res->type = STRING;
	return (res);
}

t_lexem			*ft_get_comment(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int 		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	len = (int)ft_strlen(str) - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = COMMENT;
	cur->line++;
	cur->pos = 0;
	return (res);
}