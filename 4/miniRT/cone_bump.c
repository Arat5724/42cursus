/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:03:27 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:07:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

static void	bump_cone_x(t_cone *cone, t_vector op, double *x)
{
	double		temp;
	double		temp_x;
	t_vector	oc;
	double		direct;

	oc = vector_unit(vector_outer_product(op, cone->ov));
	temp = vector_inner_product(cone->or, oc);
	temp_x = (acos(temp) / M_PI);
	if (temp_x > 1)
		temp_x = 1;
	direct = vector_inner_product(
			vector_outer_product(cone->or, oc), cone->ov);
	if (direct < 0)
		temp_x = 1 - temp_x;
	temp_x *= cone->texture->width;
	*(x) = temp_x;
}

static void	bump_cone_y(t_cone *cone, t_vector op, double *y)
{
	const double	h = vector_inner_product(cone->ov, op) / cone->height;

	*(y) = h * cone->texture->height;
}

t_rgb	bump_cone(t_cone *cone, t_vector P, t_vector *N)
{
	const t_vector	op = vector_minus(P, cone->point);
	t_rgb			normal;
	double			x;
	double			y;

	bump_cone_x(cone, op, &x);
	bump_cone_y(cone, op, &y);
	normal = color_itos(pixel_get(cone->texture->normal, x, y));
	bump_set_normal(N, normal);
	return (color_itos(pixel_get(cone->texture->diff, x, y)));
}
