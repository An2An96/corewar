/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:48:56 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/19 19:49:40 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_printf.h"

# include "op.h"

# define SECURE_MALLOC(a)	!(a) && throw_error(MEMORY_ERR)

# define STR_ERROR_SYS		COLOR_ERROR"[System Error]: "COLOR_NONE
# define MEMORY_ERR			STR_ERROR_SYS, "Not enough memory"

/*
**	Структура описывающая объект каретки
*/

typedef struct	s_carriage
{
	int				id;
	bool			carry;
	unsigned char	op_code;
	int				last_live_cycle;
	int				cycles_to_execute;
	int				position;
	void			*registers[REG_NUMBER];
}				t_carriage;

/*
**	Структура описывающая состояние виртуальной машины
*/

typedef struct	s_env
{
	unsigned char	field[MEM_SIZE];
	t_list			*carriages;
	int				last_live_champ;
	int				cycles_to_die;
	int				cycles_count;
	int				checks_count;
}				t_env;

/*
**	Структура описывающая чемпиона
*/

typedef struct	s_champion
{
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned int	prog_size;
	unsigned char	*exec_code;
}				t_champion;


int		throw_error(const char *title, const char *err);

t_env	*init_vm(t_list *champions);

void	print_memory(const void *memory, size_t size);
void	swap_bytes(void *memory, int size);

void	print_memory(const void *memory, size_t size);

#endif
