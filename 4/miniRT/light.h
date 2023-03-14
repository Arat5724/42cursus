/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:40:14 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "color.h"
# include "struct.h"
# include "vector.h"
# include "minirt.h"

t_rgb	get_color_light(t_map *map, t_lvector vectors, t_vector bt);
#endif