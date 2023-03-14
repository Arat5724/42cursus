/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:49:22 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 08:24:24 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	getstart(size_t len, char *map, char const *s1)
{
	size_t	start;

	start = 0;
	while (start < len && map[(unsigned char)*(s1 + start)])
		start ++;
	return (start);
}

static size_t	getend(size_t len, char *map, char const *s1, size_t start)
{
	size_t	end;

	end = len - 1;
	while (end > start && map[(unsigned char)*(s1 + end)])
		end --;
	return (end);
}

static void	setmap(char *map, char const *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		map[(unsigned char)*(set + i)] = 1;
		i ++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	char	map[256];
	char	*result;

	len = ft_strlen(s1);
	if (len)
	{
		ft_bzero(map, 256);
		setmap(map, set);
		start = getstart(len, map, s1);
		len = getend(len, map, s1, start) - start + 1;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result)
	{
		ft_memcpy(result, s1 + start, len);
		*(result + len) = '\0';
	}
	return (result);
}
