/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:39:09 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 20:35:09 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_u(t_info *info, va_list *ap)
{
	long long	nbr;
	char		temp[50];
	int			len;

	nbr = (long long)va_arg(*(ap), unsigned int);
	len = 0;
	if (nbr)
		dtoa(nbr, temp, &len);
	else if (!(info->dot && !info->percision))
		temp[len++] = '0';
	info->len = len;
	if (!info->dot && !info->left && info->filled == '0')
		info->percision = info->width - !(!(info->sign));
	if (len > info->percision)
		info->percision = len;
	return (p_u_return(info, temp));
}

int	p_u_return(t_info *info, char *temp)
{
	int		result1;
	int		result2;

	if (info->left)
	{
		result1 = p_u_value(info, temp);
		result2 = p_u_filled(info);
	}
	else
	{
		result1 = p_u_filled(info);
		result2 = p_u_value(info, temp);
	}
	if (result1 == -1 || result2 == -1)
		return (-1);
	else
		return (result1 + result2);
}

int	p_u_value(t_info *info, char *temp)
{
	int	tmp;
	int	result;
	int	i;

	result = 0;
	i = -1;
	while (++i < info->percision - info->len)
	{
		tmp = write(1, "0", 1);
		if (tmp == -1)
			return (-1);
		result += tmp;
	}
	tmp = write(1, temp, info->len);
	if (tmp == -1)
		return (-1);
	result += tmp;
	return (result);
}

int	p_u_filled(t_info *info)
{
	int	tmp;
	int	result;
	int	i;

	result = 0;
	i = -1;
	while (++i < info->width - info->percision)
	{
		tmp = write(1, &(info->filled), 1);
		if (tmp == -1)
			return (-1);
		result += tmp;
	}
	return (result);
}
