/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:56:30 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 17:00:55 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_dup2(int fd1, int fd2)
{
	int	success;

	success = dup2(fd1, fd2);
	if (success == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (success);
}

void	ft_cmd_not_found(char *cmd, char **path_list)
{
	if (*(cmd) != '/')
	{
		ft_putstr_fd(path_list[0], 2);
		ft_putstr_fd(": command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

int	ft_execve(char *cmd, char **cmd_list, char **envp)
{
	int	success;

	success = execve(cmd, cmd_list, envp);
	if (success == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (success);
}

int	ft_write(int fd, char *buffer, int size)
{
	int	success;

	success = write(fd, buffer, size);
	if (success == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (success);
}
