/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:34:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 16:43:46 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_info	info = {"", 0, BUFFER_SIZE, 0, 0};
	char			*str;

	if (fd_error(fd, &str, &info))
		return (0);
	while (1)
	{
		if (info.sol == BUFFER_SIZE)
		{
			buf_join(&str, info.buf + BUFFER_SIZE - (info.new), &info, 0);
			info.success = read(fd, info.buf, BUFFER_SIZE);
			if (buf_end(&str, &info))
				return (str);
			info.sol = 0;
		}
		if (info.success < BUFFER_SIZE && info.sol == (size_t)info.success)
			return (buf_join(&str, info.buf + info.sol - info.new, &info, 1));
		if (info.buf[info.sol] == '\n')
			return (buf_join(&str, info.buf + info.sol - info.new, &info, 2));
		info.sol ++;
		info.new ++;
	}
	return (str);
}
