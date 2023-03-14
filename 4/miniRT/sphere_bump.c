/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:51:02 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 12:52:10 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

static void	bump_sphere_x(t_sphere *sphere, t_vector op, double *x)
{
	double	temp;
	double	temp_x;

	op.y = 0;
	op = vector_unit(op);
	temp = op.z;
	temp_x = (acos(temp) / M_PI);
	if (temp_x > 1)
		temp_x = 1;
	if (op.x < 0)
		temp_x = 1 - temp_x;
	temp_x *= sphere->texture->width;
	*(x) = temp_x;
}

static void	bump_sphere_y(t_sphere *sphere, t_vector op, double *y)
{
	double	temp;
	double	temp_y;

	temp = op.y * -1 / sphere->radius;
	temp_y = (acos(temp) / M_PI);
	if (temp_y > 1)
		temp_y = 1;
	temp_y *= sphere->texture->height;
	*(y) = temp_y;
}

t_rgb	bump_sphere(t_sphere *sphere, t_vector P, t_vector *N)
{
	const t_vector	op = vector_minus(P, sphere->point);
	t_rgb			normal;
	double			x;
	double			y;

	bump_sphere_x(sphere, op, &x);
	bump_sphere_y(sphere, op, &y);
	normal = color_itos(pixel_get(sphere->texture->normal, x, y));
	bump_set_normal(N, normal);
	return (color_itos(pixel_get(sphere->texture->diff, x, y)));
}
