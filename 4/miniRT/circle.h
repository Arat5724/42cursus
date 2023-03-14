/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:00:04 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCLE_H
# define CIRCLE_H

# include "minirt.h"

double	get_t_circle(void *obj, t_vector A, t_vector b);
int		get_color_circle(t_map *map, t_vector A, t_vector bt, int i);
t_rgb	check_circle(t_circle *circle, t_vector P);
t_rgb	bump_circle(t_circle *circle, t_vector P, t_vector *N);
#endif