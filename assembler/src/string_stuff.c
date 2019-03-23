/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:39:46 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 17:19:20 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *ft_str_create(char const *new)
{
	int     len;
	int     i;
	char    *res;

	len = 0;
	i = 0;
	res = NULL;
	if (new == NULL)
		return (NULL);
	len = (int)ft_strlen(new);
	res = (char *)malloc(sizeof(char) * len + 1);
	CHECK_NULL(res);
	while (new[i])
	{
		res[i] = new[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void        ft_str_extend(char **str, char const *new)
{
	int     len;
	char    *tmp;

	len = 0;
	tmp = NULL;
	if (new == NULL)
		return ;
	len = (int)ft_strlen(new);
	if (len == 0)
		return ;
	if (*str == NULL)
		*str = ft_str_create(new);
	else
	{
		tmp = ft_strjoin(*str, new);
		ft_strdel(str);
		*str = tmp;
	}
}

char	*ft_strjoin_free(char *s1, char *s2, int operation)
{
	char	*str;

	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	if (!(str = (char *)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	if (operation == 1)
		free(s1);
	else if (operation == 2)
		free(s2);
	else if (operation == 3)
	{
		free(s1);
		free(s2);
	}
	return (str);
}