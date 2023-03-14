/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:50:45 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 12:51:46 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

static char	check_sphere_delta(t_sphere *sphere, t_vector op)
{
	double			temp;
	char			black;

	black = 0;
	temp = op.y * -1 / sphere->radius;
	if (temp < 0)
	{
		temp *= -1;
		black = !black;
	}
	if (0.5 < temp && temp < cos(M_PI / 6))
		black = !black;
	return (black);
}

static char	check_sphere_theta(t_vector op)
{
	double			temp;
	char			black;

	op.y = 0;
	op = vector_unit(op);
	black = 0;
	temp = op.z;
	if (temp < 0)
	{
		temp *= -1;
		black = !black;
	}
	if (0 < temp && temp < cos(M_PI / 6))
		black = !black;
	return (black);
}

t_rgb	check_sphere(t_sphere *sphere, t_vector P)
{
	const t_vector	op = vector_minus(P, sphere->point);

	if (check_sphere_theta(op) == check_sphere_delta(sphere, op))
		return (color_init(255, 255, 255));
	return (sphere->rgb);
}
