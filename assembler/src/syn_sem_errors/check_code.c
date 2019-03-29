/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:43:16 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/28 21:35:58 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int 		find_count_instructions(t_lex_list *lst)
{
	int 		count;
	int			i;
	t_lex_list	*tmp;

	i = 0;
	count = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->lexem->type == INSTRUCT)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void		check_start_instruction(t_lex_list *lst, t_errors **err)
{
	if (!lst->next)
		return (push_back_errors_list(err, SEMANTIC, NO_ARGUMENTS, lst->lexem));
	lst = lst->next;
	if (find_count_instructions(lst) > 0)
		return (push_back_errors_list(err, SYNTACTIC, EXCESS_INSTUCTION_IN_LINE, lst->lexem));
	else
		check_instructions(lst, err);
}

static void		check_start_label(t_lex_list *lst, t_errors **err)
{
	if (!lst->next)
		return ;
	lst = lst->next;
	if (lst->lexem->type != INSTRUCT)
		push_back_errors_list(err, SEMANTIC, INVALID_LEXEM_SEQUENCE, lst->lexem);
	else
		check_start_instruction(lst, err);
}

void			check_code(t_tokens *tokens, t_errors **err)
{
	int 		i;
	t_lex_list	*tmp;

	i = 0;
	while (i < tokens->count)
	{
		if ((tmp = tokens->tokenlst[i]) != NULL)
		{
			if (tmp->lexem->type == COMMAND)
			{
				i++;
				continue;
			}
			else if (tmp->lexem->type == LABEL)
				check_start_label(tmp, err);
			else if (tmp->lexem->type == INSTRUCT)
				check_start_instruction(tmp, err);
			else
				push_back_errors_list(err, SEMANTIC, INVALID_LEXEM_SEQUENCE, tmp->lexem);
		}
		i++;
	}
}