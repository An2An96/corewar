/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 20:14:42 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/22 20:19:16 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

t_lex_list	*ft_new_lex(t_lexem *content)
{
    t_lex_list	*ptr;

    ptr = (t_lex_list *)malloc(sizeof(t_lex_list));
    if (ptr == NULL)
        return (NULL);
    ptr->next = NULL;
    ptr->lexem = content;
    return (ptr);
}

void		ft_push_list(t_lex_list **alst, t_lexem *content)
{
    t_lex_list	*tmp;

    tmp = *alst;
    if (*alst == NULL)
    {
        *alst = ft_new_lex(content);
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = ft_new_lex(content);
}

t_lexical_err	*ft_new_lex_errors(int err, int addit_err, t_lexem *lexem)
{
    t_lexical_err	*ptr;

    ptr = (t_lexical_err *)malloc(sizeof(t_lexical_err));
    if (ptr == NULL)
        return (NULL);
    ptr->next = NULL;
    ptr->error_code[0] = err;
    ptr->error_code[1] = addit_err;
    ptr->lexem = lexem;
    return (ptr);
}

void		ft_push_list_lex_errors(t_lexical_err **alst, int err, int addit_err, t_lexem *lexem)
{
    t_lexical_err	*tmp;

    tmp = *alst;
    if (*alst == NULL)
    {
        *alst = ft_new_lex_errors(err, addit_err, lexem);
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = ft_new_lex_errors(err, addit_err, lexem);
}