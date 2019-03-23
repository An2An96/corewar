/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:28:12 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/23 21:52:56 by vrestles         ###   ########.fr       */
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
# define BUFF 32

enum tokens
{
						COMMAND = 1,
						STRING,
						INSTRUCT,
						COMMENT,
						LABEL,
						REG,
						SEP,
						DIR,
						DIR_LABEL,
						INDIR,
						INDIR_LABEL,
						UNDEF
};

typedef struct          s_lines
{
    int                 count;
    char                **line;
}                       t_lines;

typedef struct          s_lexem
{
    int                 type;
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

t_bool                  ft_file_name_validity(char *str);
char                    *ft_create_out_file(char *str);
void                    ft_str_extend(char **str, char const *new);
int                     ft_count_lines(char *str);
char                    **ft_lines_split(char *str);
void		            ft_push_list(t_lex_list **alst, t_lexem *content);
t_tokens                *ft_get_tokens(t_lines *lines);
char					*ft_strjoin_free(char *s1, char *s2, int operation);
t_bool					ft_is_label_char(char c);
t_bool					ft_is_undefined(char c);

t_lexem   				*ft_get_command(char *str, t_cursor *cur);
t_lexem   				*ft_get_string(t_lines *lines, t_cursor *cur);
t_lexem					*ft_get_comment(char *str, t_cursor *cur);
t_lexem   				*ft_get_separator(char *str, t_cursor *cur);
t_lexem   				*ft_get_direct(char *str, t_cursor *cur);
t_lexem   				*ft_get_direct_label(char *str, t_cursor *cur);
t_lexem   				*ft_get_registor(char *str, t_cursor *cur);
t_lexem   				*ft_get_indir_num(char *str, t_cursor *cur);
t_lexem   				*ft_get_undef(char *str, t_cursor *cur);

#endif
