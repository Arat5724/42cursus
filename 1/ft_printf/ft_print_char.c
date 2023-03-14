/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:28:45 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 19:34:45 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_c(t_info *info, va_list *ap)
{
	char	c;
	int		result1;
	int		result2;

	c = (char)va_arg(*(ap), int);
	if (info->left)
	{
		result1 = p_c_value(c);
		result2 = p_c_filled(info);
	}
	else
	{
		result1 = p_c_filled(info);
		result2 = p_c_value(c);
	}
	if (result1 == -1 || result2 == -1)
		return (-1);
	else
		return (result1 + result2);
}

int	p_per(t_info *info)
{
	char	c;
	int		result1;
	int		result2;

	c = '%';
	if (info->left)
	{
		result1 = p_c_value(c);
		result2 = p_c_filled(info);
	}
	else
	{
		result1 = p_c_filled(info);
		result2 = p_c_value(c);
	}
	if (result1 == -1 || result2 == -1)
		return (-1);
	else
		return (result1 + result2);
}

int	p_c_value(char c)
{
	return (write(1, &c, 1));
}

int	p_c_filled(t_info *info)
{
	int	i;
	int	temp;
	int	result;

	result = 0;
	i = 0;
	while (i < info->width - 1)
	{
		temp = write(1, " ", 1);
		if (temp == -1)
			return (-1);
		result += temp;
		i ++;
	}
	return (result);
}
