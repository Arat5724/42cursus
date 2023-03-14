/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:34:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/08 08:17:15 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_info	first = {.sol = BUFFER_SIZE};
	t_info			*info;
	char			*str;

	if (fd_error(fd, &str, &first, &info))
		return (0);
	while (1)
	{
		if (info->sol == BUFFER_SIZE)
		{
			buf_join(&str, info->buf + BUFFER_SIZE - info->new, info, 0);
			info->success = read(fd, info->buf, BUFFER_SIZE);
			if (buf_end(&str, info))
				return (str);
			info->sol = 0;
		}
		if (info->success < BUFFER_SIZE && info->sol == (size_t)(info->success))
			return (buf_join(&str, info->buf + info->sol - info->new, info, 1));
		if (info->buf[info->sol] == '\n')
			return (buf_join(&str, info->buf + info->sol - info->new, info, 2));
		info->sol ++;
		info->new ++;
	}
}

int	fd_error(int fd, char **str, t_info *first, t_info **info)
{
	t_info	*new;

	if (fd < 0)
		return (1);
	*(info) = first;
	while ((*(info))->next && (*(info))->fd != fd)
		(*(info)) = (*(info))->next;
	if ((*(info))->fd != fd)
	{
		new = fd_new(fd);
		new->last = *(info);
		(*(info))->next = new;
		(*(info)) = new;
	}
	*(str) = 0;
	(*(info))->len = 0;
	(*(info))->new = 0;
	return (0);
}

t_info	*fd_new(int fd)
{
	t_info	*result;

	result = (t_info *)malloc(sizeof(t_info));
	if (!result)
		return (0);
	result->next = 0;
	result->last = 0;
	result->fd = fd;
	result->sol = BUFFER_SIZE;
	return (result);
}

void	fd_del(t_info *info)
{
	t_info	*last;
	t_info	*next;

	if (!(info->fd))
		return ;
	last = info->last;
	next = info->next;
	last->next = next;
	if (next)
		next->last = last;
	free(info);
}
