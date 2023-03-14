/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:22:48 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:22:53 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector_set_def(t_vector ov)
{
	if (ov.y == 1 || ov.y == -1)
		ov.x = 1;
	if (ov.y)
		ov.y = (ov.y * ov.y - 1) / ov.y;
	else
	{
		ov.x = 0;
		ov.y = 1;
		ov.z = 0;
	}
	return (ov);
}
