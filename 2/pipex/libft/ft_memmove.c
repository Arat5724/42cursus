/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:43:04 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 07:53:12 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cpy1(char *d, char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(d + n - 1 - i) = *(s + n - 1 - i);
		i ++;
	}
}

static void	cpy2(char *d, char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		i ++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (!d && !s)
		return (0);
	if (n)
	{
		if (d > s)
			cpy1(d, s, n);
		else
			cpy2(d, s, n);
	}
	return (dst);
}
