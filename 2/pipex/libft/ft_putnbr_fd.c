/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:56:44 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 07:53:40 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	putnbr3(long long nbr, int fd, int sign, int count)
{
	if (nbr)
	{
		putnbr3(nbr / 10, fd, sign, count + 1);
		ft_putchar_fd((nbr % 10) + '0', fd);
	}
	else
	{
		if (count == 0)
			ft_putchar_fd('0', fd);
		if (sign == -1)
			ft_putchar_fd('-', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;
	int			sign;

	sign = 1;
	nbr = (long long)n;
	if (nbr < 0)
	{
		nbr *= -1;
		sign = -1;
	}
	putnbr3(nbr, fd, sign, 0);
}
