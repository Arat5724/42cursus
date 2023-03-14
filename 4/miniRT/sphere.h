/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:49:52 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 01:06:15 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"

double	get_t_sphere(void *obj, t_vector A, t_vector b);
int		get_color_sphere(t_map *map, t_vector A, t_vector bt, int i);
t_rgb	check_sphere(t_sphere *sphere, t_vector P);
int		mirror_sphere(t_map *map, t_lvector *vectors, t_vector bt);
t_rgb	bump_sphere(t_sphere *sphere, t_vector P, t_vector *N);
#endif