/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:03:45 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "minirt.h"

double	get_t_cone(void *obj, t_vector A, t_vector b);
int		get_color_cone(t_map *map, t_vector A, t_vector bt, int i);
t_rgb	check_cone(t_cone *cone, t_vector P);
t_rgb	bump_cone(t_cone *cone, t_vector P, t_vector *N);
#endif