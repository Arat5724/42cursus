/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:02:14 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 17:32:12 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_temp(char *eof)
{
	int		fd;
	char	*str;

	fd = ft_open2(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		ft_write(1, "pipe heredoc> ", 14);
		str = get_next_line(0);
		while (!str)
			str = get_next_line(0);
		if (*(str) != '\n' && !ft_strncmp(eof, str, ft_strlen(str) - 1))
		{
			free(str);
			break ;
		}
		else
		{
			ft_write(fd, str, ft_strlen(str));
			free(str);
		}
	}
	ft_close(fd);
	fd = ft_open1(".temp", O_RDONLY);
	unlink(".temp");
	return (fd);
}

void	first_bonus_cmd(int *fd, int count, char **argv, char **path_list)
{
	pid_t	pid;
	char	**cmd_list;
	int		outfile;
	int		fd2[2];

	cmd_list = get_cmd_list(argv[3], path_list);
	ft_pipe(fd2);
	pid = ft_fork();
	if (pid == 0)
	{
		outfile = open_temp(argv[2]);
		fd[0] = outfile;
		ft_cmd_not_found(cmd_list[0], path_list);
		child_process(fd, fd2, FIRST, cmd_list);
	}
	middle_bonus_cmd(fd2, count - 4, argv + 4, path_list);
	wait(0);
	free_list(cmd_list);
}

void	middle_bonus_cmd(int *fd, int count, char **argv, char **path_list)
{
	pid_t	pid;
	char	**cmd_list;
	int		fd2[2];

	if (count == 2)
	{
		last_bonus_cmd(fd, argv, path_list);
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
	middle_bonus_cmd(fd2, count - 1, argv + 1, path_list);
	wait(0);
	free_list(cmd_list);
}

void	last_bonus_cmd(int *fd, char **argv, char **path_list)
{
	pid_t	pid;
	int		outfile;
	char	**cmd_list;
	int		fd2[2];

	cmd_list = get_cmd_list(argv[0], path_list);
	pid = ft_fork();
	if (pid == 0)
	{
		outfile = ft_open2(argv[1], O_APPEND | O_WRONLY | O_CREAT, 0644);
		fd2[1] = outfile;
		ft_cmd_not_found(cmd_list[0], path_list);
		child_process(fd, fd2, LAST, cmd_list);
	}
	ft_close(fd[0]);
	ft_close(fd[1]);
	wait(0);
	free_list(cmd_list);
}
