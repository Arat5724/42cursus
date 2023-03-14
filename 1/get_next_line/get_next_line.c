/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:34:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/22 12:30:07 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_info	info;
	char			*str;

	if (fd < 0 || read(fd, info.buf, 0) == -1)
		return (0);
	str = 0;
	info.old_len = 0;
	info.new_len = 0;
	while (1)
	{
		if (info.index == (size_t)info.rbyte)
		{
			buf_join(&str, info.buf + info.rbyte - (info.new_len), &info);
			info.rbyte = read(fd, info.buf, BUFFER_SIZE);
			info.index = 0;
			if (!(info.rbyte))
				return (str);
		}
		if (info.buf[info.index] == '\n')
			return (buf_join(
					&str, info.buf + info.index++ - info.new_len++, &info));
		info.index ++;
		info.new_len ++;
	}
}
