/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:43:38 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "minirt.h"

double	get_t_plane(void *obj, t_vector A, t_vector b);
int		get_color_plane(t_map *map, t_vector A, t_vector bt, int i);
t_rgb	check_plane(t_plane	*plane, t_vector P);
t_rgb	bump_plane(t_plane *plane, t_vector P, t_vector *N);
#endif