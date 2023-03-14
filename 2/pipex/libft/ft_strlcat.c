/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:52:24 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/04 20:35:08 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	max_d;
	size_t	max_s;
	size_t	i;
	size_t	result;

	max_d = ft_strlen((const char *)dst);
	max_s = ft_strlen(src);
	if (!(max_d > dstsize || dstsize == 0))
	{
		i = 0;
		while (max_d + i < dstsize - 1 && i < max_s)
		{
			*(dst + max_d + i) = *(src + i);
			i ++;
		}
		*(dst + max_d + i) = '\0';
	}
	else
		max_d = dstsize;
	result = max_d + max_s;
	return (result);
}
