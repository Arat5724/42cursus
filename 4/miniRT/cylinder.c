/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:53:54 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:40:41 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

static double	get_t_cylinder3(
		t_cylinder *cylinder, t_vector A, t_vector b, double t)
{
	double		h;
	t_vector	pt;

	if (t > 0)
	{
		pt = vector_plus(A, vector_mul(b, t));
		h = vector_inner_product(
				vector_minus(pt, cylinder->point), cylinder->ov);
		if (0 <= h && h <= cylinder->height)
			return (t);
	}
	return (0);
}

static double	get_t_cylinder2(
		t_cylinder *cylinder, t_vector A, t_vector b, t_abcd *abcd)
{
	double		t1;
	double		t2;

	t1 = (0 - abcd->b + sqrt(abcd->d)) / abcd->a;
	t1 = get_t_cylinder3(cylinder, A, b, t1);
	t2 = (0 - abcd->b - sqrt(abcd->d)) / abcd->a;
	t2 = get_t_cylinder3(cylinder, A, b, t2);
	return (min_pos(t1, t2));
}

double	get_t_cylinder(void *obj, t_vector A, t_vector b)
{
	t_cylinder	*cylinder;
	t_vector	temp;
	t_abcd		abcd;

	cylinder = (t_cylinder *)obj;
	temp = vector_minus(A, cylinder->point);
	abcd.a = vector_size2(vector_outer_product(b, cylinder->ov));
	abcd.b = vector_inner_product(
			vector_outer_product(b, cylinder->ov),
			vector_outer_product(temp, cylinder->ov));
	abcd.c = vector_size2(vector_outer_product(temp, cylinder->ov))
		- cylinder->radius * cylinder->radius;
	abcd.d = abcd.b * abcd.b - abcd.a * abcd.c;
	if (abcd.d >= 0)
		return (get_t_cylinder2((t_cylinder *)cylinder, A, b, &abcd));
	return (0);
}

int	get_color_cylinder(t_map *map, t_vector A, t_vector bt, int i)
{
	const t_obj	*objs = map->objs;
	t_cylinder	*cylinder;
	t_rgb		rgb;
	t_vector	r;
	t_lvector	vectors;

	cylinder = (t_cylinder *)((*(objs + i)).obj);
	vectors.pt = vector_plus(A, bt);
	r = vector_plus(cylinder->point, vector_mul(cylinder->ov,
				vector_inner_product(
					vector_minus(vectors.pt, cylinder->point), cylinder->ov)));
	vectors.n = vector_unit(vector_minus(vectors.pt, r));
	if (vector_inner_product(vectors.n, bt) > 0)
		vectors.n = vector_mul(vectors.n, -1);
	if (cylinder->option == 3)
		return (mirror_sphere(map, &vectors, bt));
	if (cylinder->option == 1)
		rgb = check_cylinder(cylinder, vectors.pt);
	else if (cylinder->option == 2)
		rgb = bump_cylinder(cylinder, vectors.pt, &vectors.n);
	else
		rgb = cylinder->rgb;
	rgb = color_light(rgb, map->amb.rgb, map->amb.ratio);
	rgb = color_plus_pos(rgb, get_color_light(map, vectors, bt));
	return (color_int(rgb));
}
