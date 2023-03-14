/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:18:00 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 22:18:38 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_otype(char *str)
{
	int	result;

	result = atoi(str);
	if (!(0 <= result && result <= 4))
		parse_error();
	return (result);
}

int	parse_option(char *str)
{
	int	result;

	result = atoi(str);
	if (!(0 <= result && result <= 3))
		parse_error();
	return (result);
}

void	get_filename(char **file1, char **file2, int n)
{
	if (n == 0)
	{
		*(file1) = "texture/floor_diff.xpm";
		*(file2) = "texture/floor_nor.xpm";
	}
	else if (n == 1)
	{
		*(file1) = "texture/wall_diff.xpm";
		*(file2) = "texture/wall_nor.xpm";
	}
	else if (n == 2)
	{
		*(file1) = "texture/snow_diff.xpm";
		*(file2) = "texture/snow_nor.xpm";
	}
	else
	{
		*(file1) = "texture/forest_diff.xpm";
		*(file2) = "texture/forest_nor.xpm";
	}
}

t_texture	*get_texture(t_vars *vars, int n)
{
	t_texture	*texture;
	char		*file1;
	char		*file2;

	texture = (t_texture *)malloc(sizeof(t_texture));
	texture->diff = (t_img *)malloc(sizeof(t_img));
	texture->normal = (t_img *)malloc(sizeof(t_img));
	get_filename(&file1, &file2, n);
	texture->diff->img = mlx_xpm_file_to_image(vars->mlx,
			file1, &(texture->width), &(texture->height));
	texture->diff->addr = mlx_get_data_addr(texture->diff->img,
			&texture->diff->bits_per_pixel, &texture->diff->line_length,
			&texture->diff->endian);
	texture->normal->img = mlx_xpm_file_to_image(vars->mlx,
			file2, &(texture->width), &(texture->height));
	texture->normal->addr = mlx_get_data_addr(texture->normal->img,
			&texture->normal->bits_per_pixel, &texture->normal->line_length,
			&texture->normal->endian);
	return (texture);
}

double	parse_radius(char *str)
{
	double	result;

	result = ft_atod(str);
	if (!(0 < result && result <= 5000))
		parse_error();
	return (result);
}
