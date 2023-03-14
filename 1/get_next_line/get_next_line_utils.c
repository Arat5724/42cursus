/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:32:49 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/22 12:27:03 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buf_join(char **str, char *buffer, t_info *info)
{
	char	*new_str;
	int		i;

	if (info->index == (size_t)info->rbyte && !info->old_len && !info->new_len)
    	return (0);
	if (info->index == (size_t)info->rbyte)
		info->index = (size_t)info->rbyte;
	new_str = malloc(info->old_len + info->new_len + 1);
	if (*(str))
	{
		i = -1;
		while (++i < (int)info->old_len)
			*(new_str + i) = *(*(str) + i);
		free(*(str));
	}
	i = -1;
	while (++ i < (int)info->new_len)
		*(new_str + info->old_len + i) = *(buffer + i);
	*(new_str + info->old_len + info->new_len) = 0;
	info->old_len += info->new_len;
	info->new_len = 0;
	*(str) = new_str;
	return (*(str));
}
