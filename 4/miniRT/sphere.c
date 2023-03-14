/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:42:39 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:40:59 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

// sphere : (P(t) - O)⋅(P(t) - O) = r ^ 2
double	get_t_sphere(void *obj, t_vector A, t_vector b)
{
	const t_sphere	*sphere = (t_sphere *)obj;
	const t_vector	temp = vector_minus(A, sphere->point);
	const double	b0 = vector_inner_product(b, temp);
	const double	c0 = vector_size2(temp) - sphere->radius * sphere->radius;
	const double	d = b0 * b0 - c0;

	if (d >= 0)
		return (min_pos(0 - b0 + sqrt(d), 0 - b0 - sqrt(d)));
	return (0);
}

int	mirror_sphere(t_map *map, t_lvector *vectors, t_vector bt)
{
	double		temp;

	temp = vector_inner_product(bt, vectors->n);
	bt = vector_minus(vector_mul(vectors->n, 2 * temp), bt);
	bt = vector_unit(vector_mul(bt, -1));
	return (get_pixel_color(map, vectors->pt, bt));
}

int	get_color_sphere(t_map *map, t_vector A, t_vector bt, int i)
{
	const t_obj	*objs = map->objs;
	t_sphere	*sphere;
	t_rgb		rgb;
	t_lvector	vectors;

	sphere = (t_sphere *)((*(objs + i)).obj);
	vectors.pt = vector_plus(A, bt);
	vectors.n = vector_unit(vector_minus(vectors.pt, sphere->point));
	if (sphere->option == 3)
		return (mirror_sphere(map, &vectors, bt));
	if (sphere->option == 1)
		rgb = check_sphere(sphere, vectors.pt);
	else if (sphere->option == 2)
		rgb = bump_sphere(sphere, vectors.pt, &vectors.n);
	else
		rgb = sphere->rgb;
	rgb = color_light(rgb, map->amb.rgb, map->amb.ratio);
	rgb = color_plus_pos(rgb, get_color_light(map, vectors, bt));
	return (color_int(rgb));
}
