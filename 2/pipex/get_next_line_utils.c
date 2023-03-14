/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:32:49 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 17:25:27 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	fd_error(int fd, char **str, t_info *info)
{
	if (fd < 0)
		return (1);
	else
	{
		*(str) = 0;
		info->len = 0;
		info->new = 0;
		return (0);
	}
}

char	*buf_join(char **str, char *buffer, t_info *info, int option)
{
	char	*new_str;

	if (option == 1)
		info->sol = BUFFER_SIZE;
	if (option == 1 && !info->len && !info->new)
		return (0);
	if (option == 2)
	{
		(info->sol)++;
		(info->new)++;
	}
	new_str = (char *)malloc(sizeof(char) * (info->len) + (info->new) + 1);
	if (*(str))
	{
		ft_memcpy(new_str, *(str), info->len);
		free(*(str));
	}
	ft_memcpy(new_str + info->len, buffer, info->new);
	*(new_str + info->len + info->new) = 0;
	info->len += info->new;
	info->new = 0;
	*(str) = new_str;
	if (option == 2)
		info->sol = BUFFER_SIZE;
	return (*(str));
}

int	buf_end(char **str, t_info *info)
{
	if (info->success == -1 || (!(info->success) && !(info->len)))
	{
		free(*(str));
		*(str) = 0;
		return (1);
	}
	if (!(info->success) && info->len)
		return (1);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dst;
	s = (const char *)src;
	if (!d && !s)
		return (0);
	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		i ++;
	}
	return (dst);
}
