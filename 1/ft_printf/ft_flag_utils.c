/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 11:07:15 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 14:23:41 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	flag_init(const char **str, t_info *info)
{
	char	c;

	info_init(info);
	while (1)
	{
		c = *(*(str));
		if (c == '-' || c == '0' || c == '+' || c == ' ' || c == '#')
		{
			if (c == '-')
				info->left = 1;
			else if (c == '0' && !(info->left))
				info->filled = '0';
			else if (c == '+')
				info->sign = '+';
			else if (c == ' ' && !(info->sign))
				info->sign = ' ';
			else
				info->hash = 1;
			*(str) += 1;
		}
		else
			break ;
	}
	return (flag_atoi(str, info, 1));
}

int	flag_atoi(const char **str, t_info *info, char w)
{
	int	result;

	result = 0;
	while ('0' <= *(*(str)) && *(*(str)) <= '9')
	{
		result = result * 10 + *(*(str)) - '0';
		*(str) += 1;
	}
	if (w)
	{
		info->width = result;
		if (*(*(str)) == '.')
		{
			info->dot = 1;
			info->filled = ' ';
			*(str) += 1;
			return (flag_atoi(str, info, 0));
		}
	}
	else
		info->percision = result;
	return (flag_conversion(str, info));
}

int	flag_conversion(const char **str, t_info *info)
{
	static const char	convers[10] = {"cspdiuxX%"};
	char				conv;
	int					i;

	conv = *(*(str));
	i = 0;
	while (i < 9)
	{
		if (conv == convers[i])
		{
			info->conv = i;
			*(str) += 1;
			return (1);
		}
		i ++;
	}
	return (0);
}
