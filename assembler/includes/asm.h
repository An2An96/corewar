/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:12 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/27 22:00:58 by vrestles         ###   ########.fr       */
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

# define COLOR_BOLD		"\x1b[1m"
# define COLOR_ERROR	"\x1b[1;31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_NONE		"\x1b[0m"

enum prog_errors
{
	NO_FILE = 1,
	MORE_THAN_ONE_FILE = 2,
	CANT_OPEN_FILE = 3,
	EMPTY_FILE = 4,
	ERRORS_IN_CODE = 5
};

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

typedef struct			s_errors
{
	int 				error_code[2];
	t_lexem				*lexem;
	struct s_errors		*next;
}						t_errors;

t_bool					is_file_name_valid(char *str);

t_lines         		*read_file_into_lines(int fd, char **line);
t_tokens				*get_tokens(t_lines *lines);
t_errors 				*get_lex_errors(t_tokens *tokens);

void					push_back_lex_list(t_lex_list **alst, t_lexem *content);
void					push_back_lex_errors(t_errors **alst, int err, int addit_err, t_lexem *lexem);

t_bool					is_label_char(char c);
t_bool					is_undefined(char c);
t_bool					is_digit_sign(char c);

t_lexem   				*get_command(char *str, t_cursor *cur);
t_lexem   				*get_string(t_lines *lines, t_cursor *cur);
t_lexem					*get_comment(char *str, t_cursor *cur);
t_lexem   				*get_separator(char *str, t_cursor *cur);
t_lexem   				*get_direct(char *str, t_cursor *cur);
t_lexem   				*get_direct_label(char *str, t_cursor *cur);
t_lexem   				*get_register(char *str, t_cursor *cur);
t_lexem					*get_instruction(char *str, t_cursor *cur, int len);
t_lexem   				*get_indir_num(char *str, t_cursor *cur);
t_lexem   				*get_undef(char *str, t_cursor *cur);
t_lexem   				*get_indir_label(char *str, t_cursor *cur);
t_lexem   				*get_label(char *str, t_cursor *cur, int len);

t_lexem   				*check_instuct_label_reg(char *str, t_cursor *cur);
t_lexem   				*check_indir_or_label(char *str, t_cursor *cur);
t_lexem  				*check_label_or_undef(char *str, t_cursor *cur);

int						check_error_string(char *value);
int						check_error_command(char *value);
int						check_error_reg(char *value);
int						check_error_dir(char *value);
int						check_error_indir(char *value);
int						check_error_instruction(char *value);
int						check_error_dir_label(char *value);
int						check_error_indir_label(char *value);
int						check_error_undef(char *value);

void    				print_errors(char *filename, t_errors *lex_errors);

void					delete_str_commas(t_tokens *tokens);
void					delete_lines(t_lines **del);
void					delete_tokens(t_tokens **del);
void 					delete_lex_errors(t_errors **del);
void					delete_lexem(t_lexem **del);
void					delete_elem_lex_list(t_lex_list **lst, t_lex_list *del);
void					delete_lex_list(t_lex_list **head);

#endif
