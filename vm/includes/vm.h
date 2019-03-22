/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:48:56 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/22 13:10:36 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdarg.h>

/*
**	Libs
*/

# include "libft.h"
# include "ft_printf.h"

/*
**	Main header by subject
*/

# include "op.h"

/*
**	Macroses
*/

# define ARG_TYPE(val, num)	((val) >> (8 - (2 * (num + 1))) & 0x3)

# define SECURE_MALLOC(a)	!(a) && throw_error(MEMORY_ERR)

# define STR_ERROR_SYS		COLOR_ERROR"[System Error]: "COLOR_NONE
# define STR_ERROR_VALID	COLOR_ERROR"[Validation Error]: "COLOR_NONE
# define MEMORY_ERR			STR_ERROR_SYS, "Not enough memory"

/*
**	Structure describe carriage
*/

typedef struct	s_carriage
{
	int				id;
	bool			carry;
	unsigned char	op_code;
	int				last_live_cycle;
	int				cycles_to_execute;
	int				position;
	unsigned int	registers[REG_NUMBER];
}				t_carriage;

/*
**	Structure describe champion
*/

typedef struct	s_champion
{
	int				nbr_player;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	*exec_code;
	unsigned int	prog_size;
}				t_champion;

/*
**	Structure describe vm state
**	last_cycle_*	-	переменная хранящая номер цикла в котором произошло
						какое-то действие
**	rcount_*		-	(repeat counter) счетчик периодически скидывающий
**						свое значение (0)
**	acount_*		-	(absolute counter) абсолютный счетчик, который считает
						не скидывает значения до конца выполнения программы
*/

typedef struct	s_env
{
	unsigned char	field[MEM_SIZE];

	int				dump_nbr_cycle;

	t_champion		**champions;
	t_list			*carriages;

	int				last_live_champ;
	int				cycles_to_die;

	int				last_cycle_change_ctd;
	int				last_cycle_check;

	int				rcount_lives;
	int				acount_cycles;
	int				acount_checks;
}				t_env;

typedef int (*t_op_func)(t_env *env, t_carriage *carriage, int args_types, ...);

t_op	g_op_tab[17];

/*
**	Read
*/


void		put_champ_on_arr(int nbr_player, char *argv, t_env *env, int *mask);
void		read_args(int argc, char **argv, t_env *env);
void		check_arr_champions(int count_champion, int *mask, t_env *env);

/*
**	Main VM functions
*/

void		init_env(t_env *env);
void		vm_loop(t_env *env);

int			op_live(t_env *env, t_carriage *carriage, int args_types, ...);
int			op_ld(t_env *env, t_carriage *carriage, int args_types, ...);
void		op_st(t_carriage *carriage, unsigned int arg1, unsigned int arg2);
int			op_add(t_env *env, t_carriage *carriage, int args_types, ...);
int			op_sub(t_env *env, t_carriage *carriage, int args_types, ...);
void		op_and(t_carriage *carriage, unsigned int arg1, unsigned int arg2, unsigned int arg3);
void		op_or(t_carriage *carriage, unsigned int arg1, unsigned int arg2, unsigned int arg3);
void		op_xor(t_carriage *carriage, unsigned int arg1, unsigned int arg2, unsigned int arg3);
int			op_zjmp(t_env *env, t_carriage *carriage, int args_types, ...);
int			op_ldi(t_env *env, t_carriage *carriage, int args_types, ...);
int			op_sti(t_env *env, t_carriage *carriage, int args_types, ...);
void		op_fork(t_carriage *carriage, unsigned int arg);
void		op_lld(t_carriage *carriage, unsigned int arg1, unsigned int arg2);
void		op_lldi(t_carriage *carriage, unsigned int arg1, unsigned int arg2, unsigned int arg3);
void		op_lfork(t_carriage *carriage, unsigned int arg1);
void		op_aff(t_carriage *carriage, unsigned int arg1);

int			get_reg_value(t_carriage *carriage, char idx);

/*
**	Utils functions
*/

void		print_memory(const void *memory, size_t size);
void		swap_bytes(void *memory, int size);

/*
**	Debug
*/

void		print_champion(t_champion *champion);
void		print_carriage(t_env *env, t_carriage *carriage);

/*
**	Print
*/

void    print_players(t_env *env);

#endif
