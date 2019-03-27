/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_commas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:29:10 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/26 17:29:10 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

static void			get_rid_of_commas(char **str)
{
	char	*new;
	char	*old;
	int		len;

	len = (int)ft_strlen(*str);
	new = ft_strsub(*str, 1, (unsigned int)(len - 2));
	old = *str;
	*str = new;
	ft_strdel(&old);
}

void				delete_str_commas(t_tokens *tokens)
{
	t_lex_list	*tmp;
	int			i;

	i = 0;
	while (i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		while (tmp)
		{
			if (tmp->lexem->type == 2)
				get_rid_of_commas(&(tmp->lexem->value));
			tmp = tmp->next;
		}
		i++;
	}
}
