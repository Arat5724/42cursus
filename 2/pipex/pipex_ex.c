/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:47:01 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 15:53:49 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipe(int *fd)
{
	int	success;

	success = pipe(fd);
	if (success == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (success);
}

int	ft_fork(void)
{
	int	success;

	success = fork();
	if (success == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (success);
}

int	ft_open1(const char *filename, int option)
{
	int	fd;

	fd = open(filename, option);
	if (fd == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (fd);
}

int	ft_open2(const char *filename, int option1, int option2)
{
	int	fd;

	fd = open(filename, option1, option2);
	if (fd == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (fd);
}

int	ft_close(int fd)
{
	int	success;

	success = close(fd);
	if (success == -1)
	{
		perror("pipex: ");
		exit(1);
	}
	else
		return (success);
}
