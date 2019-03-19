/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:37:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/19 19:46:46 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	swap_bytes(void *memory, int size)
{
	int				i;
	unsigned char	tmp;
	unsigned char	*byte;

	byte = (unsigned char*)memory;
	i = 0;
	while (i < size / 2)
	{
		tmp = byte[i];
		byte[i] = byte[size - i - 1];
		byte[size - i - 1] = tmp;
		i++;
	}
}
