/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruct_label_lexems.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:53:13 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/25 20:06:17 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

t_lexem   *ft_get_label(char *str, t_cursor *cur, int len)
{
	t_lexem     *res;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = LABEL;
	cur->pos += len + 1;
	return (res);
}

static t_lexem   *ft_get_instruction(char *str, t_cursor *cur, int len)
{
	t_lexem     *res;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	res->value = ft_strsub(str, (unsigned int)cur->pos, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = INSTRUCT;
	cur->pos += len;
	return (res);
}

t_lexem   *check_instuct_label_reg(char *str, t_cursor *cur)
{
	int i;

	i = cur->pos + 1;
	if (str[cur->pos] == 'r')
		if (str[i] && (ft_isdigit(str[i]) || ft_is_digit_sign(str[i])))
			return (ft_get_registor(str, cur));
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
		if (ft_isalpha_small(str[i]))
			i++;
		else
			return (ft_get_instruction(str, cur, i - cur->pos));
	}
	return (ft_get_instruction(str, cur, i - cur->pos));
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
	len = j - cur->pos - 2;
	res->value = ft_strsub(str, (unsigned int)cur->pos + 2, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = DIR_LABEL;
	cur->pos = j;
	return (res);
}

t_lexem   *ft_get_indir_label(char *str, t_cursor *cur)
{
	t_lexem	*res;
	int		i;
	int		len;

	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	i = cur->pos + 1;
	while (str[i])
	{
		if (ft_is_label_char(str[i]))
			i++;
		else
			break ;
	}
	len = i - (cur->pos + 1);
	res->value = ft_strsub(str, (unsigned int)cur->pos + 1, (unsigned int)len);
	res->start = cur->pos;
	res->line = cur->line;
	res->type = INDIR_LABEL;
	cur->pos += len + 1;
	return (res);
}