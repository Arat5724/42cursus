/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:55:18 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 12:57:05 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

static void	bump_cylinder_x(t_cylinder *cylinder, t_vector op, double *x)
{
	double		temp;
	double		temp_x;
	t_vector	oc;
	double		direct;

	oc = vector_unit(vector_outer_product(op, cylinder->ov));
	temp = vector_inner_product(cylinder->or, oc);
	temp_x = (acos(temp) / M_PI);
	if (temp_x > 1)
		temp_x = 1;
	direct = vector_inner_product(
			vector_outer_product(cylinder->or, oc), cylinder->ov);
	if (direct < 0)
		temp_x = 1 - temp_x;
	temp_x *= cylinder->texture->width;
	*(x) = temp_x;
}

static void	bump_cylinder_y(t_cylinder *cylinder, t_vector op, double *y)
{
	const double	h = vector_inner_product(cylinder->ov, op)
		/ cylinder->height;

	*(y) = h * cylinder->texture->height;
}

t_rgb	bump_cylinder(t_cylinder *cylinder, t_vector P, t_vector *N)
{
	const t_vector	op = vector_minus(P, cylinder->point);
	t_rgb			normal;
	double			x;
	double			y;

	bump_cylinder_x(cylinder, op, &x);
	bump_cylinder_y(cylinder, op, &y);
	normal = color_itos(pixel_get(cylinder->texture->normal, x, y));
	bump_set_normal(N, normal);
	return (color_itos(pixel_get(cylinder->texture->diff, x, y)));
}
