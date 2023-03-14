/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:31:57 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 19:54:44 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_p(t_info *info, va_list *ap)
{
	unsigned long	p;
	char			temp[50];
	int				len;

	info->left = info->left;
	p = (unsigned long)va_arg(*(ap), void *);
	temp[0] = '0';
	temp[1] = 'x';
	len = 2;
	if (p)
		dtoh(p, temp, &len, 0);
	else
		temp[len++] = '0';
	info->len = len;
	return (p_p_return(info, temp));
}

int	p_p_return(t_info *info, char *temp)
{
	int		result1;
	int		result2;

	if (info->left)
	{
		result1 = p_p_value(info, temp);
		result2 = p_p_filled(info);
	}
	else
	{
		result1 = p_p_filled(info);
		result2 = p_p_value(info, temp);
	}
	if (result1 == -1 || result2 == -1)
		return (-1);
	else
		return (result1 + result2);
}

int	p_p_value(t_info *info, char *temp)
{
	return (write(1, temp, info->len));
}

int	p_p_filled(t_info *info)
{
	int	i;
	int	temp;
	int	result;

	i = 0;
	result = 0;
	while (i < info->width - info->len)
	{
		temp = write(1, " ", 1);
		if (temp == -1)
			return (-1);
		result += temp;
		i ++;
	}
	return (result);
}
