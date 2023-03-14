/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:11:03 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 00:24:04 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	parse_cam2(t_map *map)
{
	double	scale;
	double	temp;

	scale = map->cam.width / tan(map->cam.fov * M_PI / 360) / 2;
	map->cam.c = vector_set_scale(map->cam.ov, scale);
	if (!map->cam.c.x && !map->cam.c.z)
		map->cam.w = vector_init(map->cam.width * map->cam.ov.y / -2, 0, 0);
	else
	{
		temp = map->cam.width / (2 * sqrt(map->cam.c.x * map->cam.c.x
					+ map->cam.c.z * map->cam.c.z));
		map->cam.w = vector_init(map->cam.c.z * temp * -1, 0,
				map->cam.c.x * temp);
	}
	map->cam.h = vector_set_scale(vector_outer_product(
				map->cam.c, map->cam.w), map->cam.height / 2);
}

void	parse_cam(t_map *map, char *str)
{
	char	**words;

	if (!str)
		parse_error();
	words = ft_split(str, 32);
	if (ft_strlen2(words) < 5)
		parse_error();
	map->cam.point = parse_point(words[0]);
	map->cam.ov = parse_ov(words[1]);
	map->cam.fov = parse_degree(words[2]);
	map->cam.width = parse_wh(words[3]);
	map->cam.height = parse_wh(words[4]);
	parse_cam2(map);
	ft_free2(words);
	free(str);
}

void	parse_amb(t_map *map, char *str)
{
	char	**words;

	if (!str)
		parse_error();
	words = ft_split(str, 32);
	if (ft_strlen2(words) < 2)
		parse_error();
	map->amb.ratio = parse_ratio(words[0]);
	map->amb.rgb = parse_rgb(words[1]);
	ft_free2(words);
	free(str);
}

t_light	parse_light2(char *str)
{
	t_light	result;
	char	**words;

	if (!str)
		parse_error();
	words = ft_split(str, 32);
	if (ft_strlen2(words) < 3)
		parse_error();
	result.point = parse_point(words[0]);
	result.ratio = parse_ratio(words[1]);
	result.rgb = parse_rgb(words[2]);
	ft_free2(words);
	free(str);
	return (result);
}

void	parse_light(t_map *map, int fd, int size)
{
	int	i;

	map->lights = malloc(sizeof(t_light) * (size + 1));
	i = 0;
	while (i < size)
	{
		*(map->lights + i) = parse_light2(get_next_line(fd));
		i ++;
	}
	(*(map->lights + i)).ratio = 0;
}
