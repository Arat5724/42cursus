/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:59:59 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:02:10 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circle.h"

static void	bump_circle_xy(t_circle *circle, t_vector op, double *x, double *y)
{
	double	temp_x;
	double	temp_y;

	temp_x = vector_inner_product(circle->oc, op)
		/ circle->radius;
	if (temp_x < -1)
		temp_x = -1;
	if (temp_x > 1)
		temp_x = 1;
	temp_x = (temp_x + 1) / 2 * circle->texture->width;
	temp_y = vector_inner_product(circle->or, op)
		/ circle->radius;
	if (temp_y < -1)
		temp_y = -1;
	if (temp_y > 1)
		temp_y = 1;
	temp_y = (temp_y + 1) / 2 * circle->texture->height;
	*(x) = temp_x;
	*(y) = temp_y;
}

t_rgb	bump_circle(t_circle *circle, t_vector P, t_vector *N)
{
	const t_vector	op = vector_minus(P, circle->point);
	t_rgb			normal;
	double			x;
	double			y;

	bump_circle_xy(circle, op, &x, &y);
	normal = color_itos(pixel_get(circle->texture->normal, x, y));
	bump_set_normal(N, normal);
	return (color_itos(pixel_get(circle->texture->diff, x, y)));
}
