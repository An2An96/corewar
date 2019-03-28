/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:23:45 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/28 21:29:42 by vrestles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/asm.h"

void	print_semantic_err(t_errors *lex_errors)
{
	printf(COLOR_ERROR"semantic error:\t"COLOR_NONE);
	if (lex_errors->error_code[1] == NO_CODE)
		printf("no code to execute");
	else if (lex_errors->error_code[1] == NO_COMMANDS)
		printf("no commands");
	else if (lex_errors->error_code[1] == COMMAND_NAME_NOT_FOUND)
		printf("command .name not found");
	else if (lex_errors->error_code[1] == COMMAND_COMMENT_NOT_FOUND)
		printf("command .comment not found");
	else if (lex_errors->error_code[1] == COMMAND_REDEFINITION)
		printf("command redefinition ");
	else if (lex_errors->error_code[1] == NO_ARGUMENTS)
		printf("no arguments ");
	else if (lex_errors->error_code[1] == INVALID_TYPE_OF_ARGUMENT)
		printf("invalid type of argument ");
	else if (lex_errors->error_code[1] == INVALID_NUMBER_OF_ARGUMENT)
		printf("invalid number of arguments ");
	else if (lex_errors->error_code[1] == EXCESS_SIZE_COMMAND)
		printf("excess size of command ");
	else if (lex_errors->error_code[1] == INVALID_LEXEM_SEQUENCE)
		printf("invalid lexem sequence ");
}

void	print_syntactic_err(t_errors *lex_errors)
{
	printf(COLOR_ERROR"syntactic error:\t"COLOR_NONE);
	if (lex_errors->error_code[1] == WRONG_PROGRAM_STRUCTURE)
		printf("wrong program structure");
	else if (lex_errors->error_code[1] == EXCESS_INSTUCTION_IN_LINE)
		printf("excess instruction in line ");
}

void	print_lexical_err(t_errors *lex_errors)
{
	printf(COLOR_ERROR"lexical error: "COLOR_NONE);
	if (lex_errors->error_code[1] == EMPTY_VALUE)
		printf("empty value ");
	else if (lex_errors->error_code[1] == NON_EXISTENT_VALUE)
		printf("non existent value ");
	else if (lex_errors->error_code[1] == OUT_OF_RANGE_VALUE)
		printf("out of range value ");
	else if (lex_errors->error_code[1] == NON_VALID_VALUE)
		printf("non valid value ");
	else if (lex_errors->error_code[1] == NON_EXISTENT_LEXEM)
		printf("non existent lexem ");
}

void	print_type_lexem(t_errors *lex_errors)
{
	if (lex_errors->lexem->type == COMMAND)
		printf("[COMMAND]");
	else if (lex_errors->lexem->type == STRING)
		printf("[STRING]");
	else if (lex_errors->lexem->type == INSTRUCT)
		printf("[INSTRUCTION]");
	else if (lex_errors->lexem->type == COMMENT)
		printf("[COMMENT]");
	else if (lex_errors->lexem->type == LABEL)
		printf("[LABEL]");
	else if (lex_errors->lexem->type == REG)
		printf("[REGISTER]");
	else if (lex_errors->lexem->type == SEP)
		printf("[SEPARATOR]");
	else if (lex_errors->lexem->type == DIR)
		printf("[DIRECT]");
	else if (lex_errors->lexem->type == DIR_LABEL)
		printf("[DIRECT LABEL]");
	else if (lex_errors->lexem->type == INDIR)
		printf("[INDIRECT]");
	else if (lex_errors->lexem->type == INDIR_LABEL)
		printf("[INDIRECT LABEL]");
	else if (lex_errors->lexem->type == UNDEF)
		printf("[UNDEFINED]");
}

void    print_errors(char *filename, t_errors *lex_errors)
{
	while (lex_errors)
	{
		if (lex_errors->lexem != NULL)
			printf(COLOR_BOLD"%s:%d:%d: "COLOR_NONE, filename,
					lex_errors->lexem->line + 1, lex_errors->lexem->start + 1);
		else
			printf(COLOR_BOLD"%s:%d:%d: "COLOR_NONE, filename, 1, 0);
		if (lex_errors->error_code[0] == LEXICAL)
			print_lexical_err(lex_errors);
		else if (lex_errors->error_code[0] == SYNTACTIC)
			print_syntactic_err(lex_errors);
		else if (lex_errors->error_code[0] == SEMANTIC)
			print_semantic_err(lex_errors);
		if (lex_errors->lexem != NULL)
		{
			if (ft_strlen(lex_errors->lexem->value) > 20)
				printf(COLOR_GREEN "\"%.20s...\" " COLOR_NONE, lex_errors->lexem->value);
			else
				printf(COLOR_GREEN "\"%s\" " COLOR_NONE, lex_errors->lexem->value);
			print_type_lexem(lex_errors);
		}
		printf("\n");
		lex_errors = lex_errors->next;
	}
}