/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:48:24 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/04 15:09:41 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	max;

	max = ft_strlen(src);
	if (dstsize > 0)
	{
		i = 0;
		while (i < max && i < dstsize - 1)
		{
			*(dst + i) = *(src + i);
			i ++;
		}
		*(dst + i) = '\0';
	}
	return (max);
}
