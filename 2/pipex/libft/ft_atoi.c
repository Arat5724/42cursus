/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:59:04 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 08:25:36 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		result;

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
	while (*(str + i) == '0')
		i ++;
	result = 0;
	while ('0' <= *(str + i) && *(str + i) <= '9')
	{
		result = result * 10 + (*(str + i) - '0') * sign;
		i ++;
	}
	return (result);
}
