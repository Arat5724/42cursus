/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:43:03 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//t_map	*parse_test(t_vars *vars);
static int	close_window(int keycode, t_vars *vars);
static int	red_cross(t_vars *vars);
static void	isrt(char *filename);

int	main(int argc, char **argv)
{
	t_map		*map;
	t_vars		vars;
	t_img		img;

	if (argc != 2)
		parse_error();
	isrt(argv[1]);
	vars.mlx = mlx_init();
	map = parse_rt(&vars, argv[1]);
	vars.win = mlx_new_window(vars.mlx, map->cam.width, map->cam.height,
			"hello ray tracing!");
	mlx_hook(vars.win, 2, 0, close_window, &vars);
	mlx_hook(vars.win, 17, 0, red_cross, &vars);
	img.img = mlx_new_image(vars.mlx, map->cam.width, map->cam.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	put_pixels(&vars, &img, map);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}

static void	isrt(char *filename)
{
	const int	len = strlen(filename);

	if (strlen(filename) < 4)
		parse_error();
	if (!(*(filename + len - 1) == 't' && *(filename + len - 2) == 'r'
			&& *(filename + len - 3) == '.'))
		parse_error();
}

static int	close_window(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

static int	red_cross(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}
