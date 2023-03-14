/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:37:20 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:22:55 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector_init(double x, double y, double z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

double	vector_size(t_vector vec)
{
	const double	x = vec.x;
	const double	y = vec.y;
	const double	z = vec.z;

	return (sqrt(x * x + y * y + z * z));
}

double	vector_size2(t_vector vec)
{
	const double	x = vec.x;
	const double	y = vec.y;
	const double	z = vec.z;

	return (x * x + y * y + z * z);
}

t_vector	vector_unit(t_vector vec)
{
	const double	size = vector_size(vec);

	vec.x /= size;
	vec.y /= size;
	vec.z /= size;
	return (vec);
}

t_vector	vector_set_scale(t_vector vec, double scale)
{
	const double	size = vector_size(vec);
	t_vector		result;

	result.x = vec.x * scale / size;
	result.y = vec.y * scale / size;
	result.z = vec.z * scale / size;
	return (result);
}
