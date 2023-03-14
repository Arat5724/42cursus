/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:27:24 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:28:17 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

static void	handler_int(int signal)
{
	(void)signal;
	exit(2);
}

static void	writefree(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	free(str);
}

int	execute_heredoc(char *eof)
{
	int		fd;
	char	*str;

	signal(SIGINT, handler_int);
	fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "heredoc > ", 10);
		str = get_next_line(0);
		if (!str
			|| (*(str) != '\n' && !ft_strncmp(eof, str, ft_strlen(str) - 1)))
		{
			free(str);
			break ;
		}
		else
			writefree(fd, str);
	}
	close(fd);
	signal(SIGINT, handler);
	fd = open(".temp", O_RDONLY);
	unlink(".temp");
	return (fd);
}
