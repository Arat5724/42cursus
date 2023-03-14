/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:13:36 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/04 15:18:52 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	temp;
	size_t	i;

	str = (char *)s;
	temp = (char)c;
	i = 0;
	while (1)
	{
		if (*(str + i) == temp)
			return (str + i);
		if (!*(str + i))
			break ;
		i ++;
	}
	return (0);
}
