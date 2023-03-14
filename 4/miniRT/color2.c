/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:00:01 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 14:00:58 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb	color_light(t_rgb rgb, t_rgb light, double ratio)
{
	return (color_init(
			rgb.r * light.r * ratio / 255,
			rgb.g * light.g * ratio / 255,
			rgb.b * light.b * ratio / 255
		));
}

t_rgb	color_nag(t_rgb rgb)
{
	if (rgb.r > 0)
		rgb.r = 0;
	if (rgb.g > 0)
		rgb.g = 0;
	if (rgb.b > 0)
		rgb.b = 0;
	return (rgb);
}

static int	color_set(double a)
{
	if (a < 0)
		return (0);
	if (a > 255)
		return (255);
	return (a);
}

int	color_int(t_rgb rgb)
{
	const int	r = color_set(rgb.r);
	const int	g = color_set(rgb.g);
	const int	b = color_set(rgb.b);

	return ((r << 16) + (g << 8) + b);
}

t_rgb	color_itos(int color)
{
	t_rgb	result;

	result.r = color >> 16;
	result.g = (color >> 8) % (1 << 8);
	result.b = color % (1 << 8);
	return (result);
}
