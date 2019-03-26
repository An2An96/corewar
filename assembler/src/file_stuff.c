/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 15:31:51 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/25 13:06:24 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

static char     *ft_get_extension(char *str, char c)
{
    int len;

    len = (int)ft_strlen(str);
    str += len - 1;
    while (*str)
    {
        if (*str == c)
            return str;
        str--;
    }
    return str;
}

t_bool          ft_file_name_validity(char *str)
{
    char *ext;

    ext = ft_get_extension(str, '.');
    if (ft_strcmp(".s", ext) != 0)
    {
        ft_putendl("Invalid file extension!");
        return false;
    }
    return true;
}
