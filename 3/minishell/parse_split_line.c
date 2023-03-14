/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:27:53 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:13:40 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

static int	isset(char c)
{
	static const char	g_set[15] = {
		'<', '>', '|', '&', '(', ')', '\'', '\"', 9, 10, 11, 12, 13, 32, };
	int					i;

	if (!c)
		return (16);
	i = 0;
	while (i < 15)
	{
		if (c == g_set[i])
			return (i + 1);
		i ++;
	}
	return (0);
}

void	parse_char_redir_pipe(
	char **str, t_stat *status, t_token **head, t_token **tail)
{
	if (status->quote)
	{
		char_add_back(&((*(tail))->chars), char_new(*(*(str))));
		*(str) += 1;
	}
	else
	{
		if ((*(tail))->chars)
		{
			token_add_back(head, *(tail));
			*(tail) = token_new(0);
		}
		(*(tail))->chars = char_new(*(*(str)));
		*(str) += 1;
		if (isset(*(*(str))) == status->info)
		{
			char_add_back(&((*(tail))->chars), char_new(*(*(str))));
			*(str) += 1;
		}
		token_add_back(head, *(tail));
		*(tail) = token_new(0);
	}
}

void	stat_init(t_stat *status)
{
	status->quote = 0;
	status->info = 0;
	status->bracket = 0;
}

void	parse_char_char(
	char **str,	t_stat *status, t_token **head, t_token **tail)
{
	(void)head;
	(void)status;
	char_add_back(&((*(tail))->chars), char_new(*(*(str))));
	*(str) += 1;
}
//'<', '>', '|', '&', '(', ')', '\'', '\"', 9, 10, 11, 12, 13, 32,
static void (*const	g_parse_char[16])(char **str, t_stat *status,
		t_token **head, t_token **tail) = {
	parse_char_char,
	parse_char_redir_pipe, parse_char_redir_pipe, parse_char_redir_pipe,
	parse_char_and, parse_char_bracket, parse_char_bracket,
	parse_char_quote, parse_char_quote,
	parse_char_space, parse_char_space, parse_char_space,
	parse_char_space, parse_char_space, parse_char_space, };

t_token	*parse_char(char **str)
{
	t_token		*head;
	t_token		*tail;
	t_stat		status;

	head = 0;
	tail = token_new(0);
	stat_init(&status);
	while (*(*(str)))
	{
		status.info = isset(*(*(str)));
		(g_parse_char[status.info])(str, &status, &head, &tail);
	}
	if (tail->chars)
		token_add_back(&head, tail);
	else
		free(tail);
	if (status.quote || status.bracket)
	{
		free_token(head);
		return (0);
	}
	else
		return (head);
}
