/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 17:46:26 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 21:48:27 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

static t_lexem   *ft_define_lex(t_lines *lines, t_cursor *cur)
{
    if (lines->line[cur->line][cur->pos] == '.')
        return(ft_get_command(lines->line[cur->line], cur));
    else if (lines->line[cur->line][cur->pos] == '"')
        return(ft_get_string(lines, cur));
    else if (lines->line[cur->line][cur->pos] == COMMENT_CHAR ||
			lines->line[cur->line][cur->pos] == ALT_COMMENT_CHAR)
		return(ft_get_comment(lines->line[cur->line], cur));
    else if (lines->line[cur->line][cur->pos] == SEPARATOR_CHAR)
		return(ft_get_separator(lines->line[cur->line], cur));
    else if (lines->line[cur->line][cur->pos] == DIRECT_CHAR)
		return(ft_get_direct(lines->line[cur->line], cur));
    else if (lines->line[cur->line][cur->pos] == 'r')
		return(ft_get_registor(lines->line[cur->line], cur));
    else if (ft_isdigit(lines->line[cur->line][cur->pos]))
		return(ft_get_indir_num(lines->line[cur->line], cur));
    else
    	return(ft_get_undef(lines->line[cur->line], cur));
    /*
    else if (ft_isalpha(str[*i]))
        ft_get_instruction(str, i);
    else if (str[*i] == ':')
        ft_get_indir_label(str, i);
    */
}

static t_lex_list   *ft_get_lex_list(t_lines *lines, t_cursor *cur, int prev)
{
    t_lex_list  *res;
    t_lexem     *new;

    res = NULL;
    while (lines->line[cur->line][cur->pos])
    {
        if (lines->line[cur->line][cur->pos] == '\t' ||
        lines->line[cur->line][cur->pos] == ' ')
			cur->pos++;
        else
        {
        	if (prev < cur->line)
        		break ;
        	new = ft_define_lex(lines, cur);
            ft_push_list(&res, new);
        }
    }
    return (res);
}

t_tokens            *ft_get_tokens(t_lines *lines)
{
    int         curr_line;
    t_tokens    *res;
    t_cursor	*cursor;

    curr_line = 0;
    cursor = (t_cursor *)malloc(sizeof(t_cursor));
    CHECK_NULL(cursor);
    cursor->line = 0;
    cursor->pos = 0;
    res = (t_tokens *)malloc(sizeof(t_tokens));
    CHECK_NULL(res);
    res->count = lines->count;
    res->tokenlst = (t_lex_list **)malloc(sizeof(t_lex_list *) * lines->count);
    while (curr_line < lines->count)
    {
    	res->tokenlst[curr_line] = ft_get_lex_list(lines, cursor, curr_line);
    	if (cursor->line > curr_line)
    		curr_line = cursor->line;
    	else
		{
			curr_line++;
			cursor->line++;
			cursor->pos = 0;
		}
    }
    return (res);
}
