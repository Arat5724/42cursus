/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:33:07 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 16:26:30 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_PIXELS_H
# define PUT_PIXELS_H

void	put_pixels(t_vars *vars, t_img *img, t_map *map);
int		get_pixel_color(t_map *map, t_vector A, t_vector b);
#endif