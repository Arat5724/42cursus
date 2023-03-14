/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 11:09:16 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 18:19:11 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i ++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, int n)
{
	char		*d;
	const char	*s;
	int			i;

	d = (char *)dst;
	s = (const char *)src;
	if (!d && !s)
		return (0);
	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		i ++;
	}
	return (dst);
}

void	dtoh(unsigned long p, char *temp, int *len, int option)
{
	static char	hexdigit[2][17] = {{"0123456789abcdef"}, {"0123456789ABCDEF"}};

	if (p)
	{
		dtoh(p / 16, temp, len, option);
		temp[*(len)] = hexdigit[option][p % 16];
		*(len) += 1;
	}
}

void	dtoa(long long nbr, char *temp, int *len)
{
	if (nbr)
	{
		dtoa(nbr / 10, temp, len);
		temp[*(len)] = (nbr % 10) + '0';
		*(len) += 1;
	}
}
