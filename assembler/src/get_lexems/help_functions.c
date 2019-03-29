/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:15:08 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/29 15:58:07 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool		is_label_char(char c)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (true);
		i++;
	}
	return (false);
}

t_bool		is_undefined(char c)
{
	if (ft_isdigit(c))
		return (false);
	else if (ft_isalpha_small(c))
		return (false);
	else if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR || c == LABEL_CHAR ||
			c == DIRECT_CHAR || c == SEPARATOR_CHAR)
		return (false);
	else if (c == '"' || c == '.')
		return (false);
	else if (is_label_char(c) == true)
		return (false);
	return (true);
}

t_bool		is_digit_sign(char c)
{
	if (c == '-')
		return (true);
	if (c == '+')
		return (true);
	return (false);
}

int			ft_isalpha_small(int c)
{
    if (c > 127 || c < 0)
        return (0);
    if ((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
        return (1);
    return (0);
}
