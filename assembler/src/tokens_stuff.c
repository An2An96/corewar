/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:46:26 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 17:17:28 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_lexem   *ft_get_command(char *str, int *i)
{
	t_lexem     *res;
	int         j;
	int         len;

	res = NULL;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = *i + 1;
	while (str[j])
	{
		if (!ft_isalpha(str[j]))
			break ;
		j++;
	}
	len = j - *i;
	res->value = ft_strsub(str, *i, len);
	res->start = *i;
	res->type = COMMAND;
	*i = j;
	return (res);
}

static t_lexem   *ft_get_string(t_lines *lines, int *curr_line, int *i)
{
	t_lexem     *res;
	int         j;
	int         len;
	char        *tmp;
	char 		*ans;
	int 		flag;

	res = NULL;
	tmp = NULL;
	ans = ft_strnew(0);
	flag = false;
	res = (t_lexem *)malloc(sizeof(t_lexem));
	CHECK_NULL(res);
	j = *i + 1;
	res->start = *i;
	while (*curr_line < lines->count)
	{
		while (1)
		{
			if (lines->line[*curr_line][j] == '\0')
			{
				len = j - *i;
				tmp = ft_strsub(lines->line[*curr_line], *i, len);
				ans = ft_strjoin_free(ans, tmp, 1);
				ft_strdel(&tmp);
				break ;
			}
			if (lines->line[*curr_line][j] == '"')
			{
				len = j - *i + 1;
				tmp = ft_strsub(lines->line[*curr_line], *i, len);
				ans = ft_strjoin_free(ans, tmp, 1);
				ft_strdel(&tmp);
				*i = j + 1;
				flag = true;
				break ;
			}
			j++;
		}
		if (flag == true)
			break ;
		j = 0;
		*i = 0;
		(*curr_line)++;
	}
	res->value = ans;
	res->type = STRING;
	printf("%s\n",ans );
	return (res);
}

static t_lexem   *ft_define_lex(t_lines *lines, int *curr_line, int *i)
{
	if (lines->line[*curr_line][*i] == '.')
		return(ft_get_command(lines->line[*curr_line], i));
	else if (lines->line[*curr_line][*i] == '"')
		return(ft_get_string(lines, curr_line ,i));
	/*
	else if (ft_isalpha(str[*i]))
		ft_get_instruction(str, i);
	else if (str[*i] == COMMENT_CHAR || str[*i] == ALT_COMMENT_CHAR)
		ft_get_comment(str, i);
	else if (str[*i] == 'r')
		ft_get_registor(str, i);
	else if (str[*i] == SEPARATOR_CHAR)
		ft_get_separator(str, i);
	else if (str[*i] == DIRECT_CHAR)
		ft_get_direct(str, i);
	else if (ft_isdigit(str[*i]))
		ft_get_indir_num(str, i);
	else if (str[*i] == ':')
		ft_get_indir_label(str, i);
	*/
	return (NULL);
}

static t_lex_list   *ft_get_lex_list(t_lines *lines, int *curr_line)
{
	t_lex_list  *res;
	t_lexem     *new;
	int         i;

	i = 0;
	res = NULL;
	while (lines->line[*curr_line][i]) {
		if (lines->line[*curr_line][i] == ' ') {
			i++;
			continue;
		}
		else
		{
			new = ft_define_lex(lines, curr_line ,&i);
			ft_push_list(&res, new);
		}
	}
	return (res);
}

t_tokens            *ft_get_tokens(t_lines *lines)
{
	int         curr_line;
	t_tokens    *res;

	curr_line = 0;
	res = (t_tokens *)malloc(sizeof(t_tokens));
	CHECK_NULL(res);
	res->count = lines->count;
	res->tokenlst = (t_lex_list **)malloc(sizeof(t_lex_list *));
	while (curr_line < lines->count)
	{
		//res->tokenlst[i] = (t_lex_list *)malloc(sizeof(t_lex_list));
		res->tokenlst[curr_line] = ft_get_lex_list(lines, &curr_line);
		curr_line++;
	}
	return (res);
}
