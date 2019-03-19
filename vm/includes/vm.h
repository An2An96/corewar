/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:48:56 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/19 16:22:06 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"

/*
**	tmp
*/

# define REG_NUMBER				16

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
**	Структура описывающая объект каретки
*/

typedef struct	s_carriage
{
	int				cycles_to_execute;
	unsigned char	registers[REG_NUMBER];
}				t_carriage;

/*
**	Структура описывающая состояние виртуальной машины
*/

typedef struct	s_env
{
	unsigned char	*field;
	int				cycles_to_die;
}				t_env;

typedef struct	s_champion
{
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	*exec_code;
}				t_champion;

//	void	read_champion(char *name)
//	void	init_arena(t_list *champions)

t_env	*init_vm(t_champion *champions);

#endif
