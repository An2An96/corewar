/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sep_undef.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:57:34 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/25 18:19:56 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

t_lexem   *ft_get_separator(char *str, t_cursor *cur)
{
	t_lexem     *res;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strsub(str, (unsigned int)cur->pos, 1);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = SEP;
	cur->pos++;
	return (res);
}

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
	res->line = cur->line;
	res->type = UNDEF;
	cur->pos = j;
	return (res);
}

t_lexem   *check_label_or_undef(char *str, t_cursor *cur)
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
		if (ft_is_undefined(str[i]))
			i++;
		else
			return (ft_get_undef(str, cur));
	}
	return (ft_get_undef(str, cur));
}