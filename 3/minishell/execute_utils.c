/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:30:18 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:30:57 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	execute_cmd_not_found(char *cmd)
{
	ft_putstr_fd("lmsh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	if_end(t_cmd *cmds, int *exit_status)
{
	if ((cmds->lflag == 6 && *(exit_status))
		|| (cmds->lflag == 7 && !*(exit_status)))
		return (1);
	return (0);
}

void	execute_open_pipe(t_cmd *cmds, int *fd2)
{
	if (cmds->rflag == 5)
		pipe(fd2);
}

void	execute_close_pipe(t_cmd *cmds, int *fd)
{
	if (cmds->lflag == 5)
		close_fd2(fd);
}

void	execute_waitpid(t_cmd *cmds)
{
	int	stat;

	if (!(cmds->is_builtin))
		waitpid(cmds->pid, &stat, 0);
}
