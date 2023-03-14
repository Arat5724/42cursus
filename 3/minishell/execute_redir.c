/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:33:46 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:35:35 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	execute_join_redir(t_redir *head, t_redirio *inout)
{
	inout->in = 0;
	inout->out = 0;
	while (head)
	{
		if (head->info == 1 || head->info == 2)
			inout->in = head;
		else if (head->info == 3 || head->info == 4)
			inout->out = head;
		head = head->next;
	}
}

static void	execute_redir_in(t_cmd *cmds, int *fd, t_redir *in)
{
	if (cmds->lflag == 5 && in)
		close(fd[0]);
	if (cmds->lflag == 5)
		close(fd[1]);
	if (in)
	{
		if (in->info == 1)
			fd[0] = open(in->filename, O_RDONLY);
		else
			fd[0] = execute_heredoc(in->filename);
	}
	if (cmds->lflag != 5 && !in)
		fd[0] = 0;
	if (fd[0])
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

static void	execute_redir_out(t_cmd *cmds, int *fd2, t_redir *out)
{
	if (cmds->rflag == 5 && out)
		close(fd2[1]);
	if (cmds->rflag == 5)
		close(fd2[0]);
	if (out)
	{
		if (out->info == 3)
			fd2[1] = open(out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd2[1] = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (cmds->rflag != 5 && !out)
		fd2[1] = 1;
	if (fd2[1] != 1)
	{
		dup2(fd2[1], 1);
		close(fd2[1]);
	}
}

void	execute_redir_io(t_cmd *cmds, int *fd, int *fd2, t_redirio *inout)
{
	execute_redir_in(cmds, fd, inout->in);
	execute_redir_out(cmds, fd2, inout->out);
}
