/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:43:12 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:40:49 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

// plane : (P(t) - O)⋅orientation_vector = 0
double	get_t_plane(void *obj, t_vector A, t_vector b)
{
	const t_plane	*plane = (t_plane *)obj;
	const t_vector	temp = vector_minus(A, plane->point);
	const double	temp_p = vector_inner_product(b, plane->ov);
	double			temp_c;
	double			t;

	if (!temp_p)
		return (0);
	temp_c = 0 - vector_inner_product(temp, plane->ov);
	t = temp_c / temp_p;
	if (t > 0.0001)
		return (t);
	return (0);
}

int	get_color_plane(t_map *map, t_vector A, t_vector bt, int i)
{
	const t_obj	*objs = map->objs;
	t_plane		*plane;
	t_rgb		rgb;
	t_lvector	vectors;

	plane = (t_plane *)((*(objs + i)).obj);
	vectors.pt = vector_plus(A, bt);
	if (vector_inner_product(bt, plane->ov) > 0)
		vectors.n = vector_mul(vector_unit(plane->ov), -1);
	else
		vectors.n = vector_unit(plane->ov);
	if (plane->option == 3)
		return (mirror_sphere(map, &vectors, bt));
	if (plane->option == 1)
		rgb = check_plane(plane, vectors.pt);
	else if (plane->option == 2)
		rgb = bump_plane(plane, vectors.pt, &vectors.n);
	else
		rgb = plane->rgb;
	rgb = color_light(rgb, map->amb.rgb, map->amb.ratio);
	rgb = color_plus_pos(rgb, get_color_light(map, vectors, bt));
	return (color_int(rgb));
}
