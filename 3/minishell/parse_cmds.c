/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:39:03 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:45:30 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

static int	istoken(char *word)
{
	static const char	*g_token[10] = {
		"<", "<<", ">", ">>", "|", "&&", "||", "(", ")",
	};
	int					i;

	if (!word)
		return (10);
	i = 0;
	while (i < 9)
	{
		if (!ft_memcmp(g_token[i], word, ft_strlen(g_token[i]) + 1))
			return (i + 1);
		i ++;
	}
	return (0);
}

int	parse_cmds_redir(char ***str, char info, t_cmd **head, t_cmd **tail)
{
	int	file;

	(void)head;
	*(str) += 1;
	file = istoken(*(*(str)));
	if (file)
		return (1);
	redir_add_back(&((*(tail))->redirs), redir_new(ft_strdup(*(*(str))), info));
	*(str) += 1;
	return (0);
}

static int (*const	g_parse[11])(char ***str, char info,
		t_cmd **head, t_cmd **tail) = {
	parse_cmds_word,
	parse_cmds_redir, parse_cmds_redir, parse_cmds_redir, parse_cmds_redir,
	parse_cmds_end, parse_cmds_end, parse_cmds_end,
	parse_cmds_bracket_open, parse_cmds_bracket_close,
};

t_cmd	*parse_cmds(char ***str)
{
	t_cmd	*head;
	t_cmd	*tail;
	int		info;

	head = 0;
	tail = cmd_init();
	while (*(*(str)))
	{
		info = istoken(*(*(str)));
		if ((g_parse[info])(str, info, &head, &tail))
		{
			free_cmds(head);
			free_cmds(tail);
			return (0);
		}
		if (info == 9)
			return (head);
	}
	if (parse_cmds_close(str, &head, &tail))
	{
		free_cmds(head);
		free_cmds(tail);
		return (0);
	}
	return (head);
}
