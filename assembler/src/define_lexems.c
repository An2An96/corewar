/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lexems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:13:44 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 21:42:48 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

t_lexem   *ft_get_undef(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	j = cur->pos + 1;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (str[j])
	{
		if (ft_is_undefined(str[j]) == false)
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->type = UNDEF;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_indir_num(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	j = cur->pos + 1;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->type = INDIR;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_registor(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	j = cur->pos + 1;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->type = REG;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_direct_label(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = cur->pos + 2;
	while (str[j])
	{
		if (ft_is_label_char(str[j]) == false)
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->type = DIR_LABEL;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_direct(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	j = cur->pos + 1;
	if (str[j] == ':')
		return (ft_get_direct_label(str, cur));
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->type = DIR;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_separator(char *str, t_cursor *cur)
{
	t_lexem     *res;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strsub(str, (unsigned int)cur->pos, 1);
	res->start = cur->pos;
	res->type = SEP;
	cur->pos++;
	return (res);
}

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
		if (!ft_isalpha(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
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
	printf("%s\n",ans );
	return (res);
}

t_lexem			*ft_get_comment(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int 		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	len = (int)ft_strlen(str);
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->type = COMMENT;
	cur->line++;
	cur->pos = 0;
	return (res);
}