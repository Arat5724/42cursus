/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:07:53 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 14:01:06 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb	color_zero(void)
{
	t_rgb	rgb;

	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	return (rgb);
}

t_rgb	color_init(double r, double g, double b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

t_rgb	color_plus(t_rgb rgb1, t_rgb rgb2)
{
	return (color_init(rgb1.r + rgb2.r, rgb1.g + rgb2.g, rgb1.b + rgb2.b));
}

t_rgb	color_plus_pos(t_rgb rgb1, t_rgb rgb2)
{
	if (rgb2.r > 0)
		rgb1.r += rgb2.r;
	if (rgb2.g > 0)
		rgb1.g += rgb2.g;
	if (rgb2.b > 0)
		rgb1.b += rgb2.b;
	return (rgb1);
}

t_rgb	color_mul(t_rgb rgb, double c)
{
	return (color_init(rgb.r * c, rgb.g * c, rgb.b * c));
}
