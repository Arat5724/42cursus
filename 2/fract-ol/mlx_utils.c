/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 23:11:35 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/18 23:11:58 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	int			a;
	int			b;
	int			color;
	t_data		img;
	static int	(*sets[4])(int, int, t_vars *) = {mandel, julia, other, other2};

	img.img = mlx_new_image(vars->mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	a = -500;
	while (a <= 500)
	{
		b = -500;
		while (b <= 500)
		{
			color = (sets[vars->set])(a, b, vars);
			pixel_put(&img, 500 + a, 500 + b, color);
			b ++;
		}
		a ++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	mlx_destroy_image(vars->mlx, img.img);
	return (0);
}

int	mlx_start(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1000, 1000, "fract-ol!");
	vars->scope = 250;
	vars->x = 0;
	vars->y = 0;
	vars->c = 1;
	vars->color = 16711681;
	vars->color_range = 8192;
	render_next_frame(vars);
	mlx_hook(vars->win, 2, 0, close_window, vars);
	mlx_mouse_hook(vars->win, mouse_hook, vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop(vars->mlx);
	return (0);
}
