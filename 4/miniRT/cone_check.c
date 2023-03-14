/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:03:26 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:07:59 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

static char	check_cone_theta(t_cone *cone, t_vector op)
{
	double			temp;
	char			black;
	t_vector		oc;

	oc = vector_unit(vector_outer_product(op, cone->ov));
	temp = vector_inner_product(cone->or, oc);
	black = 0;
	if (temp < 0)
	{
		temp *= -1;
		black = !black;
	}
	if (0 < temp && temp < cos(M_PI / 6))
		black = !black;
	return (black);
}

static char	check_cone_delta(t_cone *cone, t_vector op)
{
	const int	h = vector_inner_product(cone->ov, op) * 6 / cone->height;

	return (h % 2);
}

t_rgb	check_cone(t_cone *cone, t_vector P)
{
	const t_vector	op = vector_minus(P, cone->point);

	if (check_cone_delta(cone, op) == check_cone_theta(cone, op))
		return (color_init(255, 255, 255));
	return (cone->rgb);
}
