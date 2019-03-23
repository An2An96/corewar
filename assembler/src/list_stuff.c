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

    ptr = (t_lex_list*)malloc(sizeof(t_lex_list));
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