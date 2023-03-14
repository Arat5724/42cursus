/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:34:25 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:06:45 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

t_word	*word_new(char *word)
{
	t_word	*result;

	result = (t_word *)malloc(sizeof(t_word));
	if (result)
	{
		result->next = 0;
		result->word = word;
	}
	return (result);
}

void	word_add_back(t_word **head, t_word *new)
{
	t_word	*tail;

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

t_redir	*redir_new(char *filename, char info)
{
	t_redir	*result;

	result = (t_redir *)malloc(sizeof(t_redir));
	if (result)
	{
		result->next = 0;
		result->filename = filename;
		result->info = info;
	}
	return (result);
}

void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*tail;

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
