/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:49:31 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 15:01:06 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

static double (*const	g_et_t_obj[5])(void *obj, t_vector A, t_vector b) = {
	get_t_plane, get_t_sphere, get_t_cylinder, get_t_circle, get_t_cone
};

char	shadow(t_map *map, t_light *light, t_vector A, t_vector b)
{
	const t_obj		*objs = map->objs;
	const double	d = vector_size(vector_minus(light->point, A));
	int				i;
	double			t;

	i = 0;
	while ((objs + i)->obj)
	{
		t = g_et_t_obj[(int)((objs + i)->info)]((objs + i)->obj, A, b);
		if (0.00001 < t && t < d - 0.0001)
			return (1);
		i ++;
	}
	return (0);
}

static void	get_diff_spec(t_light *light, t_lvector *vectors,
	t_rgb *diffuse, t_rgb *specular)
{
	double	l_n;
	double	r_v;

	vectors->l = vector_unit(vector_minus(light->point, vectors->pt));
	l_n = vector_inner_product(vectors->l, vectors->n);
	vectors->r = vector_minus(vector_mul(vectors->n, 2 * l_n), vectors->l);
	r_v = vector_inner_product(vectors->r, vectors->v);
	if (r_v < 0)
		r_v = 0;
	*(diffuse) = color_mul(light->rgb, light->ratio * l_n);
	*(specular) = color_mul(light->rgb, light->ratio * pow(r_v, 64));
}

t_rgb	get_color_light(t_map *map, t_lvector vectors, t_vector bt)
{
	t_rgb		result;
	t_rgb		diffuse;
	t_rgb		specular;
	t_light		*light;
	int			i;

	vectors.v = vector_unit(vector_mul(bt, -1));
	result = color_zero();
	i = 0;
	while ((map->lights + i)->ratio)
	{
		light = map->lights + i;
		get_diff_spec(light, &vectors, &diffuse, &specular);
		if (shadow(map, light, vectors.pt, vectors.l))
			result = color_plus(result, color_nag(diffuse));
		else
			result = color_plus(result, color_plus(diffuse, specular));
		i ++;
	}
	return (result);
}
