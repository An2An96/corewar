/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:22:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/20 20:23:16 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_add(t_carriage *carriage, unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
	ft_printf("op_add, arg1: %d, arg2: %d, arg3: %d\n", arg1, arg2, arg3);
}
