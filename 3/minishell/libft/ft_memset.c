/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:25:43 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/06 16:43:07 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*str;
	unsigned char	value;
	size_t			i;

	str = (char *)b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*(str + i) = value;
		i ++;
	}
	return (b);
}
