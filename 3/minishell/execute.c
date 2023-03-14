/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:52:51 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 13:44:45 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	execute_execve(t_cmd *cmds, char **words, int *exit_status)
{
	if (cmds->subshell)
		execute_subshell(cmds, exit_status);
	else
	{
		if (*(words))
		{
			execute_child_builtin(words);
			if (!ft_strchr(*(words), '/'))
				find_cmd(words);
			if (ft_strchr(*(words), '/'))
			{
				execve(words[0], words, g_envp);
				exit(127);
			}
			else
			{
				execute_cmd_not_found(*(words));
				close_fd(0, 1);
				exit(127);
			}
		}
		close_fd(0, 1);
		exit(0);
	}
}

void	execute_set_exit(t_cmd *cmds, int *exit_status)
{
	int	stat;

	if (!(cmds->is_builtin))
	{
		if (waitpid(cmds->pid, &stat, 0))
		{
			if (WIFEXITED(stat))
			{
				*(exit_status) = WEXITSTATUS(stat);
				if (*(exit_status) == 2)
					write(1, "\n", 1);
			}
			else if (WIFSIGNALED(stat))
			{
				write(1, "\n", 1);
				*(exit_status) = WTERMSIG(stat);
			}
		}
	}
}

void	execute_parent(t_cmd *cmds, t_redirio inout, int *fd2, int *exit_status)
{
	if (cmds->next)
	{
		if (cmds->rflag == 6 || cmds->rflag == 7 || cmds->rflag == 10)
		{
			signal(SIGINT, SIG_IGN);
			execute_set_exit(cmds, exit_status);
			execute_cmd(cmds->next, fd2, exit_status);
		}
		else if ((inout.in) && (inout.in)->info == 2)
		{
			execute_waitpid(cmds);
			execute_cmd(cmds->next, fd2, exit_status);
		}
		else
		{
			execute_cmd(cmds->next, fd2, exit_status);
			execute_waitpid(cmds);
		}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		execute_set_exit(cmds, exit_status);
	}
}

void	execute_cmd(t_cmd *cmds, int *fd, int *exit_status)
{
	char		**words;
	t_redirio	inout;
	int			fd2[2];

	if (if_end(cmds, exit_status))
		return ;
	execute_join_redir(cmds->redirs, &inout);
	execute_open_pipe(cmds, fd2);
	words = execute_join_words(cmds, cmds->words);
	if (execute_builtin_cmd(cmds, words, exit_status))
	{
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			signal(SIGINT, handler);
			signal(SIGQUIT, SIG_DFL);
			execute_redir_io(cmds, fd, fd2, &inout);
			execute_execve(cmds, words, exit_status);
		}
	}
	execute_close_pipe(cmds, fd);
	execute_parent(cmds, inout, fd2, exit_status);
	free2(words);
}

void	execute_head(t_cmd *head, int *exit_status)
{
	int	fd[2];

	execute_cmd(head, fd, exit_status);
}
