/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:36:30 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:36:57 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

static int	execute_join_words_size(t_word *head)
{
	int	i;

	i = 0;
	while (head && head->word)
	{
		i ++;
		head = head->next;
	}
	return (i);
}

char	**execute_join_words(t_cmd *cmds, t_word *head)
{
	const int			size = execute_join_words_size(head);
	int					i;
	char				**result;

	result = (char **)malloc(sizeof(char *) * (size + 1));
	*(result + size) = 0;
	i = 0;
	while (head && head->word)
	{
		*(result + i) = ft_strdup(head->word);
		i ++;
		head = head->next;
	}
	execute_is_builtin(cmds, *(result), size);
	return (result);
}

void	execute_subshell(t_cmd *cmds, int *exit_status)
{
	if (cmds->lflag == 5)
		cmds->subshell->lflag = 5;
	execute_head(cmds->subshell, exit_status);
	close(1);
	exit(*(exit_status));
}
