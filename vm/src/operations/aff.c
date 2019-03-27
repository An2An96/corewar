/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:37:40 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/27 19:25:43 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_aff(t_env *env, t_carriage *carriage, t_arg *args)
{
	if (PROC_ENDIAN)
		swap_bytes(&args[0].content, sizeof(args[0].content));
	if (VERB_LEVEL(SHOW_OPS))
		ft_putchar('\n');
	ft_putchar((char)args[0].content);
	return (-1);
}
