/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:20:06 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/19 08:08:05 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mandel_xy(t_point *p, double a1, double b1)
{
	const double	x1 = pow(p->x, 2) - pow(p->y, 2) + a1;

	p->y = 2 * p->x * p->y + b1;
	p->x = x1;
	return (pow(p->x, 2) + pow(p->y, 2));
}

int	mandel(int a, int b, t_vars *vars)
{
	t_point			p;
	const double	a1 = ((double)a) / (vars->scope) + (vars->x / 250);
	const double	b1 = ((double)b) / (vars->scope) + (vars->y / 250);
	int				n;
	const int		max = 100 + sqrt(vars->scope / 250);

	p.x = 0;
	p.y = 0;
	n = 0;
	while (n < max)
	{
		if (mandel_xy(&p, a1, b1) >= 4)
			break ;
		n ++;
	}
	if (n == max)
		return (16777215);
	return (vars->color + vars->color_range * log(n % max + 1));
}

static int	julia_xy(t_point *p, double a1, double b1)
{
	const double	x1 = pow(p->x, 2) - pow(p->y, 2) + a1;

	p->y = 2 * p->x * p->y + b1;
	p->x = x1;
	return (pow(p->x, 2) + pow(p->y, 2));
}

int	julia(int a, int b, t_vars *vars)
{
	t_point			p;
	const double	a1 = (vars->julia).x;
	const double	b1 = (vars->julia).y;
	int				n;
	const int		max = 100 + sqrt(vars->scope / 250);

	p.x = ((double)a) / (vars->scope) + (vars->x / 250);
	p.y = ((double)b) / (vars->scope) + (vars->y / 250);
	n = 0;
	while (n < max)
	{
		if (julia_xy(&p, a1, b1) >= 4)
			break ;
		n ++;
	}
	if (n == max)
		return (16777215);
	return (vars->color + vars->color_range * log(n % max + 1));
}
