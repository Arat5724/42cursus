/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:05:35 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 14:01:48 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

static t_ctemp	get_t_cone_temp(t_cone *cone, t_vector A, t_vector b)
{
	t_ctemp	temps;

	temps.temp = vector_minus(A, cone->point);
	temps.c1 = vector_inner_product(b, cone->ov);
	temps.temp2 = vector_minus(b, vector_mul(cone->ov, temps.c1));
	temps.c2 = vector_inner_product(temps.temp, cone->ov);
	temps.temp3 = vector_minus(temps.temp, vector_mul(cone->ov, temps.c2));
	return (temps);
}

static t_abcd	get_t_cone_abcd(t_cone *cone, t_ctemp temps)
{
	const double	cosa = cos(cone->degree * M_PI / 180);
	const double	sina = sin(cone->degree * M_PI / 180);
	const double	cosa2 = cosa * cosa;
	const double	sina2 = sina * sina;
	t_abcd			abcd;

	abcd.a = cosa2 * vector_size2(temps.temp2)
		- sina2 * temps.c1 * temps.c1;
	abcd.b = cosa2 * vector_inner_product(temps.temp2, temps.temp3)
		- sina2 * temps.c1 * temps.c2;
	abcd.c = cosa2 * vector_size2(temps.temp3)
		- sina2 * temps.c2 * temps.c2;
	abcd.d = abcd.b * abcd.b - abcd.a * abcd.c;
	return (abcd);
}

static double	get_t_cone_min2(t_cone *cone, t_vector A, t_vector b, double t)
{
	double		h;
	t_vector	pt;

	if (t > 0)
	{
		pt = vector_plus(A, vector_mul(b, t));
		h = vector_inner_product(vector_minus(pt, cone->point), cone->ov);
		if (0 <= h && h <= cone->height)
			return (t);
	}
	return (0);
}

static double	get_t_cone_min(t_cone *cone,
	t_vector A, t_vector b, t_abcd *abcd)
{
	double	t1;
	double	t2;

	t1 = (0 - abcd->b + sqrt(abcd->d)) / abcd->a;
	t1 = get_t_cone_min2(cone, A, b, t1);
	t2 = (0 - abcd->b - sqrt(abcd->d)) / abcd->a;
	t2 = get_t_cone_min2(cone, A, b, t2);
	return (min_pos(t1, t2));
}

double	get_t_cone(void *obj, t_vector A, t_vector b)
{
	t_cone	*cone;
	t_ctemp	temps;
	t_abcd	abcd;

	cone = (t_cone *)obj;
	temps = get_t_cone_temp(cone, A, b);
	abcd = get_t_cone_abcd(cone, temps);
	if (abcd.d >= 0)
		return (get_t_cone_min(cone, A, b, &abcd));
	return (0);
}
