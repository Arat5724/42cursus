/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:06:35 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:06:53 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

t_cmd	*cmd_init(void)
{
	t_cmd	*result;

	result = (t_cmd *)malloc(sizeof(t_cmd));
	if (result)
	{
		result->next = 0;
		result->words = 0;
		result->subshell = 0;
		result->redirs = 0;
		result->lflag = 0;
		result->rflag = 0;
	}
	return (result);
}

t_cmd	*cmd_new(t_word *words, t_redir *redirs, char lflag, char rflag)
{
	t_cmd	*result;

	result = (t_cmd *)malloc(sizeof(t_cmd));
	if (result)
	{
		result->next = 0;
		result->words = words;
		result->redirs = redirs;
		result->lflag = lflag;
		result->rflag = rflag;
		result->subshell = 0;
	}
	return (result);
}

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tail;

	if (!*(head))
		*(head) = new;
	else
	{
		tail = *(head);
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
}
