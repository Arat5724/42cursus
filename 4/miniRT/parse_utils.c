/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:22:21 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 19:31:01 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

int	ft_strlen2(char **words)
{
	int	i;

	i = 0;
	while (*(words + i))
		i ++;
	return (i);
}

void	ft_free2(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (*(words + i))
	{
		free(*(words + i));
		i ++;
	}
	free(words);
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
