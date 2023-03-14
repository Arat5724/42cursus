/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:47:31 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 17:48:47 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "color.h"
# include "vector.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	struct s_img	*diff;
	struct s_img	*normal;
	int				width;
	int				height;
}	t_texture;

typedef struct s_abcd
{
	double	a;
	double	b;
	double	c;
	double	d;
}		t_abcd;

typedef struct s_lvector
{
	struct s_vector	pt;
	struct s_vector	n;
	struct s_vector	l;
	struct s_vector	r;
	struct s_vector	v;
}		t_lvector;

typedef struct s_cam
{
	struct s_vector	point;
	struct s_vector	ov;
	double			fov;
	double			width;
	double			height;
	t_vector		c;
	t_vector		w;
	t_vector		h;
}		t_cam;

typedef struct s_amb
{
	double			ratio;
	struct s_rgb	rgb;
}		t_amb;

typedef struct s_light
{
	struct s_vector	point;
	double			ratio;
	struct s_rgb	rgb;
}		t_light;

typedef struct s_sphere
{
	struct s_vector		point;
	double				radius;
	char				option;
	struct s_rgb		rgb;
	struct s_texture	*texture;
}		t_sphere;

typedef struct s_plane
{
	struct s_vector		point;
	struct s_vector		ov;
	struct s_vector		or;
	struct s_vector		oc;
	char				option;
	struct s_rgb		rgb;
	struct s_texture	*texture;
}		t_plane;

typedef struct s_circle
{
	struct s_vector		point;
	struct s_vector		ov;
	struct s_vector		or;
	struct s_vector		oc;
	double				radius;
	char				option;
	struct s_rgb		rgb;
	struct s_texture	*texture;
}		t_circle;

typedef struct s_cylinder
{
	struct s_vector		point;
	struct s_vector		ov;
	struct s_vector		or;
	double				radius;
	double				height;
	char				option;
	struct s_rgb		rgb;
	struct s_texture	*texture;
}		t_cylinder;

typedef struct s_ctemp
{
	struct s_vector	temp;
	double			c1;
	struct s_vector	temp2;
	double			c2;
	struct s_vector	temp3;
}		t_ctemp;

typedef struct s_cone
{
	struct s_vector		point;
	struct s_vector		ov;
	struct s_vector		or;
	double				degree;
	double				height;
	char				option;
	struct s_rgb		rgb;
	struct s_texture	*texture;
}		t_cone;

typedef struct s_obj
{
	void	*obj;
	char	info;
}		t_obj;

typedef struct s_map
{
	struct s_cam		cam;
	struct s_amb		amb;
	struct s_light		*lights;
	struct s_obj		*objs;
}		t_map;

#endif