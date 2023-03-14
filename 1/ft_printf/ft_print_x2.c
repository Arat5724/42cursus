/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:49:34 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/11 20:57:31 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_x_value2(t_info *info, char *temp, int option)
{
	static char	lowup[2][3] = {{"0x"}, {"0X"}};
	int			result;
	int			i;
	int			tmp;

	result = 0;
	tmp = write(1, lowup[option], 2);
	if (tmp == -1)
		return (-1);
	result += tmp;
	i = -1;
	while (++i < info->percision - info->len)
	{
		tmp = write(1, "0", 1);
		if (tmp == -1)
			return (-1);
		result += tmp;
	}
	tmp = write(1, temp, info->len - 2);
	if (tmp == -1)
		return (-1);
	result += tmp;
	return (result);
}
