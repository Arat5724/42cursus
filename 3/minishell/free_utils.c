/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:59:57 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:06:14 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	free2(char **str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		free(*(str + i));
		i ++;
	}
	free(str);
}

void	free3(char ***str)
{
	int	i;
	int	j;

	i = 0;
	while (*(str + i))
	{
		j = 0;
		while (*(*(str + i) + j))
		{
			free(*(*(str + i) + j));
			j ++;
		}
		free(*(str + i));
		i ++;
	}
	free(str);
}

void	free_words(t_word *words)
{
	t_word	*next;

	while (words)
	{
		next = words->next;
		free(words->word);
		free(words);
		words = next;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*next;

	while (redirs)
	{
		next = redirs->next;
		free(redirs->filename);
		free(redirs);
		redirs = next;
	}
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*next;

	while (head)
	{
		next = head->next;
		free_words(head->words);
		free_cmds(head->subshell);
		free_redirs(head->redirs);
		free(head);
		head = next;
	}
}
