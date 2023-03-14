/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:03:26 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:40:30 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

int	get_color_cone(t_map *map, t_vector A, t_vector bt, int i)
{
	const t_obj	*objs = map->objs;
	t_cone		*cone;
	t_rgb		rgb;
	t_vector	r;
	t_lvector	vectors;

	cone = (t_cone *)((*(objs + i)).obj);
	vectors.pt = vector_plus(A, bt);
	r = vector_plus(cone->point, vector_mul(cone->ov,
				vector_size(vector_minus(vectors.pt, cone->point))
				/ cos(cone->degree * M_PI / 180)));
	vectors.n = vector_unit(vector_minus(vectors.pt, r));
	if (vector_inner_product(vectors.n, bt) > 0)
		vectors.n = vector_mul(vectors.n, -1);
	if (cone->option == 3)
		return (mirror_sphere(map, &vectors, bt));
	if (cone->option == 1)
		rgb = check_cone(cone, vectors.pt);
	else if (cone->option == 2)
		rgb = bump_cone(cone, vectors.pt, &vectors.n);
	else
		rgb = cone->rgb;
	rgb = color_light(rgb, map->amb.rgb, map->amb.ratio);
	rgb = color_plus_pos(rgb, get_color_light(map, vectors, bt));
	return (color_int(rgb));
}
