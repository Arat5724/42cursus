/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:04:27 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/18 23:10:37 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i ++;
	return (i);
}

static double	ft_atod_result(char *str)
{
	int		i;
	int		j;
	double	result;

	i = 0;
	result = 0;
	while ('0' <= *(str + i) && *(str + i) <= '9')
	{
		result = result * 10 + *(str + i) - '0';
		i ++;
	}
	if (*(str + i) != '.')
		return (result);
	j = 1;
	while ('0' <= *(str + i + j) && *(str + i + j) <= '9')
	{
		result += (*(str + i + j) - '0') * pow(10, -j);
		j ++;
	}
	return (result);
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;

	i = 0;
	while ((9 <= *(str + i) && *(str + i) <= 13) || *(str + i) == ' ')
		i ++;
	sign = 1;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			sign = -1;
		i ++;
	}
	return (sign * ft_atod_result(str + i));
}

void	print_argument(void)
{
	printf("Bad argument!\nuseage :\n");
	printf("./fractol 0     : Mandelbrot Set\n");
	printf("./fractol 1 a b : Julia Set\n");
	printf("./fractol 2     : Other\n");
	printf("./fractol 3     : Other2\n");
}
