/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:59:58 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:40:24 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circle.h"

static double	get_t_circle_in(
	t_circle *circle, t_vector A, t_vector b, double t)
{
	t_vector	op;
	double		size;

	op = vector_minus(vector_plus(A, vector_mul(b, t)), circle->point);
	size = vector_size2(op);
	if (0 <= size && size <= circle->radius * circle->radius)
		return (t);
	return (0);
}

double	get_t_circle(void *obj, t_vector A, t_vector b)
{
	t_circle	*circle;
	t_vector	temp;
	double		temp_p;
	double		temp_c;
	double		t;

	circle = (t_circle *)obj;
	temp = vector_minus(A, circle->point);
	temp_p = vector_inner_product(b, circle->ov);
	if (!temp_p)
		return (0);
	temp_c = 0 - vector_inner_product(temp, circle->ov);
	t = temp_c / temp_p;
	if (t > 0.0001)
		return (get_t_circle_in(circle, A, b, t));
	return (0);
}

int	get_color_circle(t_map *map, t_vector A, t_vector bt, int i)
{
	const t_obj	*objs = map->objs;
	t_circle	*circle;
	t_rgb		rgb;
	t_lvector	vectors;

	circle = (t_circle *)((*(objs + i)).obj);
	vectors.pt = vector_plus(A, bt);
	if (vector_inner_product(bt, circle->ov) > 0)
		vectors.n = vector_mul(vector_unit(circle->ov), -1);
	else
		vectors.n = vector_unit(circle->ov);
	if (circle->option == 3)
		return (mirror_sphere(map, &vectors, bt));
	if (circle->option == 1)
		rgb = check_circle(circle, vectors.pt);
	else if (circle->option == 2)
		rgb = bump_circle(circle, vectors.pt, &vectors.n);
	else
		rgb = circle->rgb;
	rgb = color_light(rgb, map->amb.rgb, map->amb.ratio);
	rgb = color_plus_pos(rgb, get_color_light(map, vectors, bt));
	return (color_int(rgb));
}
