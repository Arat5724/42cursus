/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:31:30 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/18 23:17:50 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_vars *vars)
{
	double	value;

	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
	{
		value = 50 * ((double)250 / vars->scope);
		if (keycode == 123)
			vars->x -= value;
		if (keycode == 124)
			vars->x += value;
		if (keycode == 125)
			vars->y += value;
		if (keycode == 126)
			vars->y -= value;
		render_next_frame(vars);
	}
	else if (keycode == 18 || keycode == 19 || keycode == 20)
		key_hook2(keycode, vars);
	return (0);
}

int	key_hook2(int keycode, t_vars *vars)
{
	if (keycode == 18 && vars->c != 1)
	{
		vars->c = 1;
		vars->color = 16711681;
		vars->color_range = 8192;
	}
	else if (keycode == 19 && vars->c != 2)
	{
		vars->c = 2;
		vars->color = 65280;
		vars->color_range = 255;
	}
	else if (keycode == 20 && vars->c != 3)
	{
		vars->c = 3;
		vars->color = 0;
		vars->color_range = 16777215;
	}
	render_next_frame(vars);
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	double	real_x;
	double	real_y;
	double	temp_x;
	double	temp_y;
	double	new_scope;

	real_x = (x - 500) * (250 / (vars->scope)) + vars->x;
	real_y = (y - 500) * (250 / (vars->scope)) + vars->y;
	temp_x = real_x - vars->x;
	temp_y = real_y - vars->y;
	if (mousecode == 4 || mousecode == 5)
	{
		if (mousecode == 4)
			new_scope = vars->scope * ZOOM;
		else
			new_scope = vars->scope / ZOOM;
		vars->x = vars->x + temp_x * (new_scope - vars->scope) / new_scope;
		vars->y = vars->y + temp_y * (new_scope - vars->scope) / new_scope;
		vars->scope = new_scope;
		printf("scope = %.f\n", vars->scope / 250);
		render_next_frame(vars);
	}
	return (0);
}
