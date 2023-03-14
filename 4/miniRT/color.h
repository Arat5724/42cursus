/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:51:24 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 14:01:05 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}		t_rgb;

t_rgb	color_zero(void);
t_rgb	color_init(double r, double g, double b);
t_rgb	color_plus(t_rgb rgb1, t_rgb rgb2);
t_rgb	color_plus_pos(t_rgb rgb1, t_rgb rgb2);
t_rgb	color_mul(t_rgb rgb, double c);

t_rgb	color_nag(t_rgb rgb);
t_rgb	color_light(t_rgb rgb, t_rgb light, double ratio);
int		color_int(t_rgb rgb);
t_rgb	color_itos(int color);

#endif