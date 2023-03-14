/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_line3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:03:45 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:04:09 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	free_char(t_char *c)
{
	t_char	*next;

	while (c)
	{
		next = c->next;
		free(c);
		c = next;
	}
}

void	free_token(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free_char(token->chars);
		free(token);
		token = next;
	}
}
