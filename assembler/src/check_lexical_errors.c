/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexical_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrestles <vrestles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:56:24 by vrestles          #+#    #+#             */
/*   Updated: 2019/03/26 19:35:54 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"
#include "inc/operations.h"

static int		check_error_command(char *value)
{
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	else if (ft_strcmp(value, NAME_CMD_STRING + 1) != 0
			 && ft_strcmp(value, COMMENT_CMD_STRING + 1) != 0)
		return (NON_EXISTENT_VALUE);
	return (0);
}

static int		check_error_string(char *value)
{
	int len;
	char c;

	c = '"';
	if (value == NULL)
		return (NON_VALID_VALUE);
	len = (int)ft_strlen(value);
	if (len == 0)
		return (NON_VALID_VALUE);
	if (value[len - 1] == c)
		return (0);
	return (NON_VALID_VALUE);
}

static int		check_error_instruction(char *value)
{
	int	i;
	i = 0;
	while (g_op_tab[i].op_code)
	{
		if (ft_strcmp(g_op_tab[i].cmd, value) == 0)
			return (0);
		i++;
	}
	return (NON_EXISTENT_VALUE);
}

static int 			check_number_error(char *value, long long *nb)
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

static int		check_error_reg(char *value)
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

static int		check_error_dir(char *value)
{
	long long nb;

	nb = 0;
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	return(check_number_error(value, &nb));
}
static int		check_error_dir_label(char *value)
{
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	return (0);
}

static int		check_error_indir(char *value)
{
	long long nb;

	nb = 0;
	return(check_number_error(value, &nb));
}

static int		check_error_indir_label(char *value)
{
	if (ft_strlen(value) == 0)
		return (EMPTY_VALUE);
	return (0);
}

static int		check_error_undef(char *value)
{
	return (NON_EXISTENT_LEXEM);
}

int 				check_lex_errors(t_lexem *lexem)
{
	if (lexem->type == COMMAND)
		return (check_error_command(lexem->value));
	else if (lexem->type == STRING)
		return (check_error_string(lexem->value));
	else if (lexem->type == INSTRUCT)
		return (check_error_instruction(lexem->value));
	else if (lexem->type == REG)
		return (check_error_reg(lexem->value));
	else if (lexem->type == DIR)
		return (check_error_dir(lexem->value));
	else if (lexem->type == DIR_LABEL)
		return (check_error_dir_label(lexem->value));
	else if (lexem->type == INDIR)
		return (check_error_indir(lexem->value));
	else if (lexem->type == INDIR_LABEL)
		return (check_error_indir_label(lexem->value));
	else if (lexem->type == UNDEF)
		return (check_error_undef(lexem->value));
	return (0);
}

t_lexical_err 		*ft_get_lex_errors(t_tokens *tokens)
{
	int				i;
	int 			addit_err;
	t_lexical_err	*res;
	t_lex_list		*tmp;

	i = 0;
	res = NULL;
	while (i < tokens->count)
	{
		tmp = tokens->tokenlst[i];
		while (tmp)
		{
			if ((addit_err = check_lex_errors(tmp->lexem)))
				ft_push_list_lex_errors(&res, 1, addit_err, tmp->lexem);
			tmp = tmp->next;
		}
		i++;
	}
	return (res);
}