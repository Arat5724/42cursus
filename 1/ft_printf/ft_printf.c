/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:55:26 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 20:55:34 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
** %[flags][width][.precision]type
 */
int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, str);
	len = ft_printf_init(&str, &ap);
	va_end(ap);
	return (len);
}

int	ft_printf_init(const char **str, va_list *ap)
{
	int		len;
	int		result;
	t_info	info;

	ihatenorm(&len, &result);
	while (*(*(str)))
	{
		if (*(*(str)) == '%')
		{
			*(str) += 1;
			flag_init(str, &info);
			result = print_init(&info, ap);
			if (pferror(result, &len))
				break ;
		}
		else
		{
			result = write(1, *(str), 1);
			*(str) += 1;
			if (pferror(result, &len))
				break ;
		}
	}
	return (len);
}

void	ihatenorm(int *len, int *result)
{
	*(len) = 0;
	*(result) = 0;
}

int	pferror(int result, int *len)
{
	if (result == -1)
	{
		*(len) = -1;
		return (1);
	}
	else
	{
		*(len) += result;
		return (0);
	}
}

void	info_init(t_info *info)
{
	info->hash = 0;
	info->left = 0;
	info->filled = ' ';
	info->sign = 0;
	info->width = 0;
	info->dot = 0;
	info->percision = 0;
	info->conv = 0;
}
