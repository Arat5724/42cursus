/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:18:59 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 09:40:15 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wordcpy(char const *s, char **result, int count, int wordlen)
{
	*(result + count - 1) = (char *)malloc(sizeof(char) * (wordlen + 1));
	if (*(result + count - 1))
	{
		ft_memcpy(*(result + count - 1), s, wordlen);
		*(*(result + count - 1) + wordlen) = 0;
		return (1);
	}
	else
		return (0);
}

static int	ft_split01(char const *s, char *map, char **result, size_t len)
{
	size_t	i;
	size_t	count;
	size_t	wordlen;
	char	now;
	char	last;

	last = 1;
	count = 0;
	i = -1;
	while (++ i <= len)
	{
		now = map[(unsigned char)*(s + i)];
		if (last && !now)
		{
			count ++;
			wordlen = 1;
		}
		else if (!last && !now)
			wordlen ++;
		else if (!last && now)
			if (!wordcpy(s + i - wordlen, result, count, wordlen))
				return (0);
		last = now;
	}
	return (1);
}

static size_t	wc(char const *s, char *map, size_t *len)
{
	size_t	i;
	size_t	count;
	char	now;
	char	last;

	last = 1;
	count = 0;
	i = 0;
	while (*(s + i))
	{
		now = map[(unsigned char)*(s + i)];
		if (last && !now)
			count ++;
		last = now;
		i ++;
	}
	*(len) = i;
	return (count);
}

static void	setmap(char *map, char const *set)
{
	size_t	i;

	ft_bzero(map, 256);
	map[0] = 1;
	i = 0;
	while (*(set + i))
	{
		map[(unsigned char)*(set + i)] = 1;
		i ++;
	}
}

char	**ft_split_set(char const *s, char const *set)
{
	size_t	count;
	size_t	len;
	size_t	i;
	char	map[256];
	char	**result;

	setmap(map, set);
	count = wc(s, map, &len);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (result)
	{
		if (ft_split01(s, map, result, len))
			*(result + count) = 0;
		else
		{
			i = -1;
			while (*(result + (++i)))
				free(*(result + i));
			free(result);
			result = 0;
		}
	}
	return (result);
}
