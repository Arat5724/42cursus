/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:24:55 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 07:56:31 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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

static int	ft_split01(char const *s, char c, char **result, size_t len)
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
		now = (*(s + i) == c || *(s + i) == '\0');
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

static size_t	wc(char const *s, char c, size_t *len)
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
		now = (*(s + i) == c);
		if (last && !now)
			count ++;
		last = now;
		i ++;
	}
	*(len) = i;
	return (count);
}

static void	free_result(char **result)
{
	size_t	i;

	i = 0;
	while (*(result + i))
	{
		free(*(result + i));
		i ++;
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	size_t	len;
	char	**result;

	count = wc(s, c, &len);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (result)
	{
		if (ft_split01(s, c, result, len))
			*(result + count) = 0;
		else
		{
			free_result(result);
			return (0);
		}
	}
	return (result);
}
