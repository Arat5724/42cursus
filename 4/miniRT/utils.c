/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:10:48 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:26:13 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	min_pos(double a, double b)
{
	if (a > 0.001 && b < 0.001)
		return (a);
	if (b > 0.001 && a < 0.001)
		return (b);
	if (a > 0.001 && b > 0.001)
	{
		if (a > b)
			return (b);
		else
			return (a);
	}
	return (0);
}

void	bump_set_normal(t_vector *N, t_rgb normal)
{
	N->x *= normal.r / 255;
	N->y *= normal.g / 255;
	N->z *= normal.b / 255;
}

int	pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
