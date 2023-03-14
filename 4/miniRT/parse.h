/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:32:11 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 23:36:39 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"
# include <string.h>
# include <math.h>
# include <stdlib.h>

char		**ft_split(char const *s, char c);
void		parse_error(void);
int			ft_strlen2(char **words);
void		ft_free2(char **words);
double		ft_atod(char *str);
t_rgb		parse_rgb(char *str);
t_vector	parse_point(char *str);
t_vector	parse_ov(char *str);
t_map		*map_init(void);
int			parse_degree(char *str);
int			parse_wh(char *str);
double		parse_ratio(char *str);
void		parse_cam(t_map *map, char *str);
void		parse_amb(t_map *map, char *str);
t_light		parse_light2(char *str);
int			parse_otype(char *str);
int			parse_option(char *str);
void		get_filename(char **file1, char **file2, int n);
t_texture	*get_texture(t_vars *vars, int n);
t_plane		*parse_plane(t_vars *vars, char **words);
t_plane		*parse_plane(t_vars *vars, char **words);
double		parse_radius(char *str);
t_sphere	*parse_sphere(t_vars *vars, char **words);
t_cylinder	*parse_cylinder(t_vars *vars, char **words);
t_circle	*parse_circle(t_vars *vars, char **words);
t_cone		*parse_cone(t_vars *vars, char **words);
t_obj		parse_obj2(t_vars *vars, char *str);
void		parse_objs(t_vars *vars, t_map *map, int fd, int size);
void		parse_light(t_map *map, int fd, int size);
t_map		*parse_rt(t_vars *vars, char *filename);
#endif