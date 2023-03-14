/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:12:36 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"

double	min_pos(double a, double b);
void	bump_set_normal(t_vector *N, t_rgb normal);
int		pixel_get(t_img *data, int x, int y);
void	pixel_put(t_img *data, int x, int y, int color);
#endif