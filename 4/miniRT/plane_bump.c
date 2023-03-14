/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:46:52 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 12:48:31 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

static void	bump_plane_xy(t_plane *plane, t_vector op, double *x, double *y)
{
	double			temp_x;
	double			temp_y;

	temp_x = (int)(vector_inner_product(plane->oc, op) * 10)
		% plane->texture->width;
	if (temp_x < 0)
		temp_x += plane->texture->width;
	temp_y = (int)(vector_inner_product(plane->or, op) * 10)
		% plane->texture->height;
	if (temp_y < 0)
		temp_y += plane->texture->height;
	*(x) = temp_x;
	*(y) = temp_y;
}

t_rgb	bump_plane(t_plane *plane, t_vector P, t_vector *N)
{
	const t_vector	op = vector_minus(P, plane->point);
	t_rgb			normal;
	double			x;
	double			y;

	bump_plane_xy(plane, op, &x, &y);
	normal = color_itos(pixel_get(plane->texture->normal, x, y));
	bump_set_normal(N, normal);
	return (color_itos(pixel_get(plane->texture->diff, x, y)));
}
