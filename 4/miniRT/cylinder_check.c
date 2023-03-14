/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:55:10 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 12:58:47 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

static char	check_cylinder_theta(t_cylinder *cylinder, t_vector op)
{
	double			temp;
	char			black;
	t_vector		oc;

	oc = vector_unit(vector_outer_product(op, cylinder->ov));
	temp = vector_inner_product(cylinder->or, oc);
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

static char	check_cylinder_delta(t_cylinder *cylinder, t_vector op)
{
	const int	h = vector_inner_product(cylinder->ov, op) * 6
		/ cylinder->height;

	return (h % 2);
}

t_rgb	check_cylinder(t_cylinder *cylinder, t_vector P)
{
	const t_vector	op = vector_minus(P, cylinder->point);

	if (check_cylinder_delta(cylinder, op)
		== check_cylinder_theta(cylinder, op))
		return (color_init(255, 255, 255));
	return (cylinder->rgb);
}
