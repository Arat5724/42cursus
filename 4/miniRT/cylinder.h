/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:54:07 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "minirt.h"

double	get_t_cylinder(void *obj, t_vector A, t_vector b);
int		get_color_cylinder(t_map *map, t_vector A, t_vector bt, int i);
t_rgb	check_cylinder(t_cylinder *cylinder, t_vector P);
t_rgb	bump_cylinder(t_cylinder *cylinder, t_vector P, t_vector *N);
#endif