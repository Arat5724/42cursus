/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:18:27 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 08:16:56 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*res;
	char	cc;
	size_t	i;

	str = (char *)s;
	cc = (char)c;
	res = 0;
	i = 0;
	while (1)
	{
		if (*(str + i) == cc)
			res = str + i;
		if (!*(str + i))
			break ;
		i ++;
	}
	return (res);
}
