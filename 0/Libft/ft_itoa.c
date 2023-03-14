/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:14:04 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 07:49:50 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	putnbr2(long long nbr, char *temp, int *len, int sign)
{
	if (nbr)
	{
		putnbr2(nbr / 10, temp, len, sign);
		temp[*(len)] = (nbr % 10) + '0';
		*(len) += 1;
	}
	else
	{
		if (sign == -1)
		{
			temp[*(len)] = '-';
			*(len) += 1;
		}
	}
}

static void	putzero(char *temp, int *len)
{
	temp[0] = '0';
	*(len) += 1;
}

char	*ft_itoa(int n)
{
	long long	nbr;
	int			sign;
	int			len;
	char		temp[50];
	char		*result;

	sign = 1;
	nbr = (long long)n;
	if (nbr < 0)
	{
		nbr *= -1;
		sign = -1;
	}
	len = 0;
	if (nbr)
		putnbr2(nbr, temp, &len, sign);
	else
		putzero(temp, &len);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result)
	{
		ft_memcpy(result, temp, len);
		*(result + len) = 0;
	}
	return (result);
}
