/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:36:22 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/19 20:19:43 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

inline static char	get_hex_char(char octet)
{
	return ((octet < 10 ? '0' : ('a' - 10)) + octet);
}

void				print_memory(const void *memory, size_t size)
{
	int i;
	int octets;

	i = 0;
	octets = 0;
	while (i < size)
	{
		ft_putchar(get_hex_char(((unsigned char*)memory)[i] >> 4));
		ft_putchar(get_hex_char(((unsigned char*)memory)[i] & 0xF));
		octets++;
		if (octets % 2 == 0)
			write(1, " ", 1);
		if (octets % 16 == 0)
			write(1, "\n", 1);
		i++;
	}
}
