/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 08:17:01 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 19:57:54 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_id(t_info *info, va_list *ap)
{
	long long	nbr;
	char		temp[50];
	int			len;

	nbr = (long long)va_arg(*(ap), int);
	p_id_abs(&nbr, info);
	len = 0;
	if (nbr)
		dtoa(nbr, temp, &len);
	else if (!(info->dot && !info->percision))
		temp[len++] = '0';
	len += !(!(info->sign));
	info->len = len;
	if (!info->dot && !info->left && info->filled == '0')
		info->percision = info->width - !(!(info->sign));
	if (len > info->percision)
		info->percision = len;
	else if (info->sign)
		info->percision += 1;
	return (p_id_return(info, temp));
}

int	p_id_return(t_info *info, char *temp)
{
	int		result1;
	int		result2;

	if (info->left)
	{
		result1 = p_id_value(info, temp);
		result2 = p_id_filled(info);
	}
	else
	{
		result1 = p_id_filled(info);
		result2 = p_id_value(info, temp);
	}
	if (result1 == -1 || result2 == -1)
		return (-1);
	else
		return (result1 + result2);
}

void	p_id_abs(long long *nbr, t_info *info)
{
	if (*(nbr) < 0)
	{
		info->sign = '-';
		*(nbr) *= -1;
	}
}

int	p_id_value(t_info *info, char *temp)
{
	int	tmp;
	int	result;
	int	i;

	result = 0;
	if (info->sign)
	{
		tmp = write(1, &(info->sign), 1);
		if (tmp == -1)
			return (-1);
		result += tmp;
	}
	i = -1;
	while (++i < info->percision - info->len)
	{
		tmp = write(1, "0", 1);
		if (tmp == -1)
			return (-1);
		result += tmp;
	}
	tmp = write(1, temp, info->len - !(!(info->sign)));
	if (tmp == -1)
		return (-1);
	result += tmp;
	return (result);
}

int	p_id_filled(t_info *info)
{
	int	temp;
	int	result;
	int	i;

	result = 0;
	i = -1;
	while (++i < info->width - info->percision)
	{
		temp = write(1, " ", 1);
		if (temp == -1)
			return (-1);
		result += temp;
	}
	return (result);
}
