/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_structures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:50:51 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/27 21:11:17 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void			delete_lex_errors(t_errors **del)
{
	if (*del == NULL)
		return ;
	free(*del);
	(*del) = NULL;
}

void			delete_lines(t_lines **del)
{
	int	i;

	i = 0;
	if (*del == NULL)
		return ;
	while (i < (*del)->count)
	{
		ft_strdel(&((*del)->line[i]));
		i++;
	}
	free(*del);
	*del = NULL;
}

void			delete_lexem(t_lexem **del)
{
	char *str;

	str = (*del)->value;
	ft_strdel(&str);
	free(*del);
	(*del) = NULL;
}

void			delete_lex_list(t_lex_list **head)
{
	t_lex_list *tmp;

	tmp = *head;
	while (tmp)
	{
		delete_lexem(&(tmp->lexem));
		tmp = tmp->next;
	}
	free(*head);
	(*head) = NULL;
}

void			delete_tokens(t_tokens **del)
{
	int i;

	i = 0;
	if (*del == NULL)
		return ;
	while (i < (*del)->count)
	{
		delete_lex_list(&((*del)->tokenlst[i]));
		i++;
	}
	free(*del);
	*del = NULL;
}
