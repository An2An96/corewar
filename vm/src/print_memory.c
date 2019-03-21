/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:36:22 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/21 15:15:07 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

inline static char	get_hex_char(char octet)
{
	return ((octet < 10 ? '0' : ('a' - 10)) + octet);
}

inline static void	print_memory_chars(const void *memory)
{
	int i;

	while (i < 16)
	{
		write(1, ft_isprint(*((char*)memory + i)) ? memory + i : ".", 1);
		i++;
	}
	write(1, "\n", 1);
}

void				print_memory(const void *memory, size_t size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_putchar(get_hex_char(((unsigned char*)memory)[i] >> 4));
		ft_putchar(get_hex_char(((unsigned char*)memory)[i] & 0xF));
		i++;
		if (i % 2 == 0)
			write(1, " ", 1);
		if (i % 16 == 0)
			print_memory_chars(memory + i - 16);
	}
}
