/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 20:37:40 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/29 11:08:17 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	op_aff(t_env *env, t_carriage *carriage, t_arg *args)
{
	(void)carriage;
	if (DIFF_ENDIAN)
		swap_bytes(&args[0].content, sizeof(args[0].content));
	if (VERB_LEVEL(SHOW_OPS))
		ft_putchar('\n');
	ft_putchar((char)args[0].content);
	return (-1);
}
