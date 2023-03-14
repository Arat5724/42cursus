/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:20:01 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/29 19:26:58 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	close_fd2(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
