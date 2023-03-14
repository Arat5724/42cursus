/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:14:28 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:46:04 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

t_obj	parse_obj2(t_vars *vars, char *str)
{
	t_obj	result;
	char	**words;

	if (!str)
		parse_error();
	words = ft_split(str, 32);
	if (!words || ft_strlen2(words) < 5)
		parse_error();
	result.info = parse_otype(words[0]);
	if (result.info == 0)
		result.obj = (void *)parse_plane(vars, words + 1);
	else if (result.info == 1)
		result.obj = (void *)parse_sphere(vars, words + 1);
	else if (result.info == 2)
		result.obj = (void *)parse_cylinder(vars, words + 1);
	else if (result.info == 3)
		result.obj = (void *)parse_circle(vars, words + 1);
	else
		result.obj = (void *)parse_cone(vars, words + 1);
	ft_free2(words);
	free(str);
	return (result);
}

void	parse_objs(t_vars *vars, t_map *map, int fd, int size)
{
	int	i;

	map->objs = malloc(sizeof(t_obj) * (size + 1));
	i = 0;
	while (i < size)
	{
		*(map->objs + i) = parse_obj2(vars, get_next_line(fd));
		i ++;
	}
	(*(map->objs + i)).obj = 0;
}

t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->lights = 0;
	map->objs = 0;
	return (map);
}

t_map	*parse_rt(t_vars *vars, char *filename)
{
	t_map	*map;
	int		fd;
	int		size;
	char	*str;

	map = map_init();
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		parse_error();
	parse_cam(map, get_next_line(fd));
	parse_amb(map, get_next_line(fd));
	str = get_next_line(fd);
	size = atoi(str);
	free(str);
	if (!size || size > 5)
		parse_error();
	parse_light(map, fd, size);
	str = get_next_line(fd);
	size = atoi(str);
	free(str);
	if (!size || size > 30)
		parse_error();
	parse_objs(vars, map, fd, size);
	return (map);
}
