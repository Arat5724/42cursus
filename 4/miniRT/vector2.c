/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:22:08 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:23:02 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vector_inner_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vector_outer_product(t_vector a, t_vector b)
{
	return (vector_init(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		));
}

t_vector	vector_plus(t_vector a, t_vector b)
{
	return (vector_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector	vector_minus(t_vector a, t_vector b)
{
	return (vector_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vector	vector_mul(t_vector vec, double d)
{
	return (vector_init(vec.x * d, vec.y * d, vec.z * d));
}
