/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:14:48 by rtroll            #+#    #+#             */
/*   Updated: 2019/03/23 17:14:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_split(char **arr)
{
	char **tmp;

	tmp = arr;
	while (*arr != NULL)
	{
		ft_strdel(arr);
		arr++;
	}
	free(tmp);
}

static	char	*ft_strtrimc(char const *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	while (s[i] == c)
		i++;
	j = 0;
	while (s[j])
		j++;
	j--;
	while (s[j] == c)
		j--;
	return (ft_strsub(s, i, j - i + 1));
}

size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		flag;
	int		i;

	count = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static	void	ft_make_split(char **ptr, size_t words, char *tr, char c)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		if (tr[j] == '\0')
			ptr[i++] = ft_strsub(tr, start, j - start);
		start = j;
		while (tr[j])
		{
			if (tr[j] == c)
			{
				ptr[i] = ft_strsub(tr, start, j - start);
				i++;
				while (tr[j] == c)
					j++;
				break ;
			}
			j++;
		}
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	size_t	words;
	char	*trimed_str;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	ptr = (char **)malloc(sizeof(char**) * (words + 1));
	if (ptr == NULL)
		return (NULL);
	trimed_str = ft_strtrimc(s, c);
	ft_make_split(ptr, words, trimed_str, c);
	ptr[words] = 0;
	ft_strdel(&trimed_str);
	return (ptr);
}
