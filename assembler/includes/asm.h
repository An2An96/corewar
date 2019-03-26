/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:12 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/26 15:21:39 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ASM_H
# define ASM_ASM_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# include "../libft/libft.h"
# include "op.h"

# define CHECK_NULL(x) if (x == NULL) return (NULL)
# define CHECK_VOID(x) if (x == NULL) return
# define BUFF 32

enum tokens
{
    COMMAND = 1,
    STRING = 2,
    INSTRUCT = 3,
    COMMENT = 4,
    LABEL = 5,
    REG = 6,
    SEP = 7,
    DIR = 8,
    DIR_LABEL = 9,
    INDIR = 10,
    INDIR_LABEL = 11,
    UNDEF = 12
};

enum errors
{
	LEXICAL = 1,
	SYNTACTIC = 2,
	SEMANTIC = 3
};

enum lexical_errors
{
	EMPTY_VALUE = 1,
	NON_EXISTENT_VALUE = 2,
	OUT_OF_RANGE_VALUE = 3,
	NON_VALID_VALUE = 4,
	NON_EXISTENT_LEXEM = 5
};

typedef struct          s_lines
{
    int                 count;
    char                **line;
}                       t_lines;

typedef struct          s_lexem
{
    int                 type;
    int 				line;
    int                 start;
    char                *value;
}                       t_lexem;

typedef struct          s_lex_list
{
    struct s_lexem      *lexem;
    struct s_lex_list   *next;
}                       t_lex_list;

typedef struct          s_tokens
{
    int                 count;
    struct s_lex_list   **tokenlst;

}                       t_tokens;

typedef struct			s_cursor
{
	int 				line;
	int 				pos;
}						t_cursor;

typedef struct			s_lexical_err
{
	int 				error_code[2];
	t_lexem				*lexem;
	struct s_lexical_err	*next;
}						t_lexical_err;

t_bool					ft_file_name_validity(char *str);
void					ft_str_extend(char **str, char const *new);
int						ft_count_lines(char *str);
char					**ft_lines_split(char *str);
void					ft_push_list(t_lex_list **alst, t_lexem *content);
t_tokens				*ft_get_tokens(t_lines *lines);
t_bool					ft_is_label_char(char c);
t_bool					ft_is_undefined(char c);
t_bool					ft_is_digit_sign(char c);
t_lexical_err			*ft_new_lex_errors(int err, int addit_err, t_lexem *lexem);

t_lexem   				*ft_get_command(char *str, t_cursor *cur);
t_lexem   				*ft_get_string(t_lines *lines, t_cursor *cur);
t_lexem					*ft_get_comment(char *str, t_cursor *cur);
t_lexem   				*ft_get_separator(char *str, t_cursor *cur);
t_lexem   				*ft_get_direct(char *str, t_cursor *cur);
t_lexem   				*ft_get_direct_label(char *str, t_cursor *cur);
t_lexem   				*ft_get_registor(char *str, t_cursor *cur);
t_lexem   				*ft_get_indir_num(char *str, t_cursor *cur);
t_lexem   				*ft_get_undef(char *str, t_cursor *cur);
t_lexem   				*check_instuct_label_reg(char *str, t_cursor *cur);
t_lexem   				*ft_get_indir_label(char *str, t_cursor *cur);
t_lexem   				*ft_get_label(char *str, t_cursor *cur, int len);
t_lexem   				*check_indir_or_label(char *str, t_cursor *cur);
t_lexem  				*check_label_or_undef(char *str, t_cursor *cur);

t_lexical_err 			*ft_get_lex_errors(t_tokens *tokens);
void					ft_push_list_lex_errors(t_lexical_err **alst, int err, int addit_err, t_lexem *lexem);
void    				print_errors(char *filename, t_lexical_err *lex_errors);

t_op					*get_op();

#endif
