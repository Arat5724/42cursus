/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:09:14 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double (*const	g_et_t_obj[5])(void *obj, t_vector A, t_vector b) = {
	get_t_plane, get_t_sphere, get_t_cylinder, get_t_circle, get_t_cone
};

static int (*const		g_et_color_obj[5])(t_map *map,
		t_vector A, t_vector bt, int i) = {
	get_color_plane, get_color_sphere, get_color_cylinder,
	get_color_circle, get_color_cone
};

int	get_pixel_color(t_map *map, t_vector A, t_vector b)
{
	const t_obj	*objs = map->objs;
	int			i;
	int			info[2];
	double		t;
	double		temp_t;

	info[0] = 0;
	info[1] = 0;
	t = 0;
	i = 0;
	while ((objs + i)->obj)
	{
		temp_t = g_et_t_obj[(int)((objs + i)->info)]((objs + i)->obj, A, b);
		if (temp_t && (!t || temp_t < t))
		{
			t = temp_t;
			info[0] = (objs + i)->info;
			info[1] = i;
		}
		i ++;
	}
	if (!t)
		return (0);
	return (g_et_color_obj[info[0]](map, A, vector_mul(b, t), info[1]));
}

static t_vector	get_ray_b(t_cam *cam, double x, double y)
{
	t_vector		w;
	t_vector		h;

	w = vector_mul(cam->w, x * 2 / cam->width);
	h = vector_mul(cam->h, y * 2 / cam->height);
	return (vector_unit(vector_plus(cam->c, vector_plus(w, h))));
}

void	put_pixels(t_vars *vars, t_img *img, t_map *map)
{
	int				x;
	int				y;
	const t_vector	a = map->cam.point;
	const int		w = map->cam.width / 2;
	const int		h = map->cam.height / 2;

	(void)vars;
	y = 0 - h;
	while (y <= h)
	{
		x = 0 - w;
		while (x <= w)
		{
			pixel_put(img, x + w, y + h,
				get_pixel_color(map, a, get_ray_b(&(map->cam), x, y)));
			x ++;
		}
		y ++;
	}
}
