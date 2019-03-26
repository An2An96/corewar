/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lexems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:13:44 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/26 12:34:42 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

t_lexem   *check_indir_or_label(char *str, t_cursor *cur)
{
	int i;

	i = cur->pos + 1;
	while (str[i])
	{
		if (ft_is_label_char(str[i]))
			i++;
		else if (str[i] == LABEL_CHAR)
			return (ft_get_label(str, cur, i - cur->pos));
		else
			break ;
	}
	i = cur->pos + 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (ft_get_indir_num(str, cur));
	}
	return (ft_get_indir_num(str, cur));
}

t_lexem   *ft_get_indir_num(char *str, t_cursor *cur)
{
	t_lexem     *res;
	int         j;
	int         len;

	j = cur->pos + 1;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	while (ft_is_digit_sign(str[j]))
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos;
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
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
	while (ft_is_digit_sign(str[j]))
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = REG;
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
	while (ft_is_digit_sign(str[j]))
		j++;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			break ;
		j++;
	}
	len = j - cur->pos - 1;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = DIR;
	cur->pos = j;
	return (res);
}