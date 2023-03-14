/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_line2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:00:48 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:13:35 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	parse_char_and(
	char **str,	t_stat *status, t_token **head, t_token **tail)
{
	if (status->quote || *(*(str) + 1) != '&')
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
		char_add_back(&((*(tail))->chars), char_new('&'));
		char_add_back(&((*(tail))->chars), char_new('&'));
		token_add_back(head, *(tail));
		*(tail) = token_new(0);
		*(str) += 2;
	}
}

void	parse_char_bracket(
	char **str,	t_stat *status, t_token **head, t_token **tail)
{
	if (status->quote)
	{
		char_add_back(&((*(tail))->chars), char_new(*(*(str))));
		*(str) += 1;
	}
	else
	{
		if (status->info == 5)
			status->bracket += 1;
		else
			status->bracket -= 1;
		if ((*(tail))->chars)
		{
			token_add_back(head, *(tail));
			*(tail) = token_new(0);
		}
		(*(tail))->chars = char_new(*(*(str)));
		token_add_back(head, *(tail));
		*(tail) = token_new(0);
		*(str) += 1;
	}
}

void	parse_char_quote(
	char **str,	t_stat *status, t_token **head, t_token **tail)
{
	(void)head;
	if (status->quote && status->quote == status->info)
		status->quote = 0;
	else if (!(status->quote))
		status->quote = status->info;
	else
		char_add_back(&((*(tail))->chars), char_new(*(*(str))));
	*(str) += 1;
}

void	parse_char_space(
	char **str,	t_stat *status, t_token **head, t_token **tail)
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
		*(str) += 1;
	}
}
