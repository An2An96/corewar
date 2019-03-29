/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_reg_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:42:05 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/29 15:46:59 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_number_error(char *value, long long *nb)
{
	int			i;
	int 		sign;

	i = 0;
	sign = 1;
	if (value[i] == '-')
		sign = -1;
	if (value[i] == '+')
		return (NON_VALID_VALUE);
	else if (value[1] && !ft_isdigit(value[1]))
		return (NON_VALID_VALUE);
	while (value[i] != '\0')
	{
		*nb = *nb * 10 + (value[i] - '0');
		if (*nb > 2147483647)
			return (OUT_OF_RANGE_VALUE);
		i++;
	}
	*nb = sign * (*nb);
	return (0);
}

int			check_error_reg(char *value)
{
	long long	nb;
	int			ret;

	nb = 0;
	ret = 0;
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	ret = check_number_error(value, &nb);
	if (nb < 1 || nb > REG_NUMBER)
		return (OUT_OF_RANGE_VALUE);
	return (ret);
}

int			check_error_dir(char *value)
{
	long long nb;

	nb = 0;
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	return(check_number_error(value, &nb));
}

int			check_error_indir(char *value)
{
	long long nb;

	nb = 0;
	return(check_number_error(value, &nb));
}
