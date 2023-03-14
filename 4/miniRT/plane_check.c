/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:45:59 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 12:48:27 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

static char	check_plane_delta(t_vector op, t_vector or)
{
	char	black;
	double	temp;

	temp = vector_inner_product(op, or);
	black = 0;
	if (temp < 0)
	{
		temp *= -1;
		black = !black;
	}
	if ((int)(temp / 100) % 2)
		black = !black;
	return (black);
}

t_rgb	check_plane(t_plane	*plane, t_vector P)
{
	const t_vector	op = vector_minus(P, plane->point);

	if (check_plane_delta(op, plane->oc) == check_plane_delta(op, plane->or))
		return (color_init(255, 255, 255));
	return (plane->rgb);
}
