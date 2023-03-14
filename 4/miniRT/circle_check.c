/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:00:00 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:02:03 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circle.h"

t_rgb	check_circle(t_circle *circle, t_vector P)
{
	const t_vector	op = vector_unit(vector_minus(P, circle->point));
	double			temp;
	char			black;

	temp = vector_inner_product(circle->or, op);
	black = 0;
	if (temp < 0)
	{
		temp *= -1;
		black = !black;
	}
	if (0 < temp && temp < cos(M_PI / 6))
		black = !black;
	if (black)
		return (color_init(255, 255, 255));
	return (circle->rgb);
}
