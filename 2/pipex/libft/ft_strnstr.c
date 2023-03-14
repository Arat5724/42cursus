/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:44:15 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 09:15:37 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*(needle))
		return ((char *)haystack);
	i = 0;
	while (i < len && *(haystack + i))
	{
		j = 0;
		while (*(needle + j) && *(haystack + i + j) && i + j < len
			&& *(haystack + i + j) == *(needle + j))
			j ++;
		if (!*(needle + j))
			return ((char *)(haystack + i));
		if (!*(haystack + i + j))
			break ;
		i ++;
	}
	return (0);
}
