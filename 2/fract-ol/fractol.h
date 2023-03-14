/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:14:47 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/18 23:12:45 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# ifndef ZOOM
#  define ZOOM 2
# endif

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	double	scope;
	double	x;
	double	y;
	int		set;
	t_point	julia;
	char	c;
	int		color;
	int		color_range;
}	t_vars;

int		render_next_frame(t_vars *vars);
void	pixel_put(t_data *data, int x, int y, int color);
int		close_window(int keycode, t_vars *vars);
int		mlx_start(t_vars *vars);

int		mouse_hook(int mousecode, int x, int y, t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
int		key_hook2(int keycode, t_vars *vars);

int		mandel(int a, int b, t_vars *vars);
int		julia(int a, int b, t_vars *vars);
int		other(int a, int b, t_vars *vars);
int		other2(int a, int b, t_vars *vars);

double	ft_atod(char *s);
int		ft_strlen(char *s);
void	print_argument(void);

#endif