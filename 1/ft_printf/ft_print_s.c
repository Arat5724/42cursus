/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:11:03 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 20:00:42 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_s(t_info *info, va_list *ap)
{
	int		result1;
	int		result2;
	char	*s;

	s = va_arg(*(ap), char *);
	if (!s)
		s = "(null)";
	info->len = ft_strlen(s);
	if (info->percision > info->len)
		info->percision = info->len;
	if (info->left)
	{
		result1 = p_s_value(info, s);
		result2 = p_s_filled(info);
	}
	else
	{
		result1 = p_s_filled(info);
		result2 = p_s_value(info, s);
	}
	if (result1 == -1 || result2 == -1)
		return (-1);
	else
		return (result1 + result2);
}

int	p_s_value(t_info *info, char *s)
{
	if (info->dot)
		return (write(1, s, info->percision));
	return (write(1, s, info->len));
}

int	p_s_filled(t_info *info)
{
	int	temp;
	int	result;
	int	i;
	int	limit;

	result = 0;
	if (info->dot)
		limit = info->width - info->percision;
	else
		limit = info->width - info->len;
	i = 0;
	while (i < limit)
	{
		temp = write(1, " ", 1);
		if (temp == -1)
			return (-1);
		result += temp;
		i ++;
	}
	return (result);
}
