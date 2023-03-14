/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:31:31 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/29 14:40:53 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

int	join_size(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i ++;
		token = token->next;
	}
	return (i);
}

int	join_word_size(t_char *chars)
{
	int	i;

	i = 0;
	while (chars)
	{
		i ++;
		chars = chars->next;
	}
	return (i);
}

void	join_word(char *dst, t_char *c)
{
	int	i;

	i = 0;
	while (c)
	{
		*(dst + i) = c->c;
		i ++;
		c = c->next;
	}
	*(dst + i) = 0;
}

char	**join_token(t_token *token)
{
	const int	size = join_size(token);
	int			i;
	int			word_size;
	char		**result;

	result = (char **)malloc(sizeof(char *) * (size + 1));
	*(result + size) = 0;
	i = 0;
	while (token)
	{
		word_size = join_word_size(token->chars);
		*(result + i) = (char *)malloc(sizeof(char) * (word_size + 1));
		join_word(*(result + i), token->chars);
		i ++;
		token = token->next;
	}
	return (result);
}
