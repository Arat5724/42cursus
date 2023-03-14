/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:42:23 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:42:48 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

int	parse_cmds_end(char ***str, char info, t_cmd **head, t_cmd **tail)
{
	(*(tail))->rflag = info;
	cmd_add_back(head, *(tail));
	if (!((*(tail))->words || (*(tail))->subshell || (*(tail))->redirs))
	{
		*(tail) = 0;
		return (1);
	}
	*(tail) = cmd_init();
	(*(tail))->lflag = info;
	*(str) += 1;
	return (0);
}

int	parse_cmds_bracket_open(char ***str, char info, t_cmd **head, t_cmd **tail)
{
	t_cmd	*subshell;

	(void)head;
	(void)info;
	if ((*(tail))->words || (*(tail))->redirs)
		return (1);
	*(str) += 1;
	subshell = parse_cmds(str);
	if (!subshell)
		return (1);
	(*(tail))->subshell = subshell;
	return (0);
}

int	parse_cmds_bracket_close(char ***str, char info, t_cmd **head, t_cmd **tail)
{
	(*(tail))->rflag = info;
	cmd_add_back(head, *(tail));
	if (!((*(tail))->words || (*(tail))->subshell || (*(tail))->redirs))
	{
		*(tail) = 0;
		return (1);
	}
	*(tail) = cmd_init();
	(*(tail))->lflag = info;
	*(str) += 1;
	return (0);
}

int	parse_cmds_word(char ***str, char info, t_cmd **head, t_cmd **tail)
{
	(void)head;
	(void)info;
	if ((*(tail))->subshell)
		return (1);
	word_add_back(&((*(tail))->words), word_new(ft_strdup(*(*(str)))));
	*(str) += 1;
	return (0);
}

int	parse_cmds_close(char ***str, t_cmd **head, t_cmd **tail)
{
	(void)str;
	cmd_add_back(head, *(tail));
	if (!((*(tail))->words || (*(tail))->subshell || (*(tail))->redirs))
	{
		*(tail) = 0;
		return (1);
	}
	return (0);
}
