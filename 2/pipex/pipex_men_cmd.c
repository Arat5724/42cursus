/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_men_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:51:58 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 15:48:41 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, int *fd2, int status, char **cmd_list)
{
	if (status != FIRST)
		ft_close(fd[1]);
	if (status != LAST)
		ft_close(fd2[0]);
	ft_dup2(fd[0], 0);
	ft_dup2(fd2[1], 1);
	ft_close(fd[0]);
	ft_close(fd2[1]);
	execve(cmd_list[0], cmd_list, 0);
	exit(1);
}

void	first_cmd(int *fd, int count, char **argv, char **path_list)
{
	pid_t	pid;
	int		infile;
	char	**cmd_list;
	int		fd2[2];

	cmd_list = get_cmd_list(argv[2], path_list);
	ft_pipe(fd2);
	pid = ft_fork();
	if (pid == 0)
	{
		infile = ft_open1(argv[1], O_RDONLY);
		fd[0] = infile;
		ft_cmd_not_found(cmd_list[0], path_list);
		child_process(fd, fd2, FIRST, cmd_list);
	}
	middle_cmd(fd2, count - 3, argv + 3, path_list);
	wait(0);
	free_list(cmd_list);
}

void	middle_cmd(int *fd, int count, char **argv, char **path_list)
{
	pid_t	pid;
	char	**cmd_list;
	int		fd2[2];

	if (count == 2)
	{
		last_cmd(fd, argv, path_list);
		return ;
	}
	cmd_list = get_cmd_list(argv[0], path_list);
	ft_pipe(fd2);
	pid = ft_fork();
	if (pid == 0)
	{
		ft_cmd_not_found(cmd_list[0], path_list);
		child_process(fd, fd2, MIDDLE, cmd_list);
	}
	ft_close(fd[0]);
	ft_close(fd[1]);
	middle_cmd(fd2, count - 1, argv + 1, path_list);
	wait(0);
	free_list(cmd_list);
}

void	last_cmd(int *fd, char **argv, char **path_list)
{
	pid_t	pid;
	int		outfile;
	char	**cmd_list;
	int		fd2[2];

	cmd_list = get_cmd_list(argv[0], path_list);
	pid = ft_fork();
	if (pid == 0)
	{
		outfile = ft_open2(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd2[1] = outfile;
		ft_cmd_not_found(cmd_list[0], path_list);
		child_process(fd, fd2, LAST, cmd_list);
	}
	ft_close(fd[0]);
	ft_close(fd[1]);
	wait(0);
	free_list(cmd_list);
}
