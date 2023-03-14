/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_line_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:58:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:58:18 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

t_char	*char_new(char c)
{
	t_char	*result;

	result = (t_char *)malloc(sizeof(t_char));
	if (result)
	{
		result->next = 0;
		result->c = c;
	}
	return (result);
}

void	char_add_back(t_char **head, t_char *new)
{
	t_char	*tail;

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

t_token	*token_new(t_char *chars)
{
	t_token	*result;

	result = (t_token *)malloc(sizeof(t_token));
	if (result)
	{
		result->next = 0;
		result->chars = chars;
	}
	return (result);
}

void	token_add_back(t_token **head, t_token*new)
{
	t_token	*tail;

	if (new->chars)
	{
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
}
