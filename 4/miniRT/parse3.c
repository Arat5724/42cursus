/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:15:30 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 01:16:22 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_plane	*parse_plane(t_vars *vars, char **words)
{
	t_plane	*plane;
	int		n;

	if (ft_strlen2(words) < 4)
		parse_error();
	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->point = parse_point(words[0]);
	plane->ov = parse_ov(words[1]);
	plane->or = vector_unit(vector_set_def(plane->ov));
	plane->oc = vector_unit(vector_outer_product(plane->ov, plane->or));
	plane->option = parse_option(words[2]);
	if (plane->option == 0 || plane->option == 1)
		plane->rgb = parse_rgb(words[3]);
	else if (plane->option == 2)
	{
		n = parse_option(words[3]);
		plane->texture = get_texture(vars, n);
	}
	return (plane);
}

t_sphere	*parse_sphere(t_vars *vars, char **words)
{
	t_sphere	*sphere;
	int			n;

	if (ft_strlen2(words) < 4)
		parse_error();
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->point = parse_point(words[0]);
	sphere->radius = parse_radius(words[1]);
	sphere->option = parse_option(words[2]);
	if (sphere->option == 0 || sphere->option == 1)
		sphere->rgb = parse_rgb(words[3]);
	else if (sphere->option == 2)
	{
		n = parse_option(words[3]);
		sphere->texture = get_texture(vars, n);
	}
	return (sphere);
}

t_cylinder	*parse_cylinder(t_vars *vars, char **words)
{
	t_cylinder	*cylinder;
	int			n;

	if (ft_strlen2(words) < 6)
		parse_error();
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->point = parse_point(words[0]);
	cylinder->ov = parse_ov(words[1]);
	cylinder->or = vector_unit(vector_set_def(cylinder->ov));
	cylinder->radius = parse_radius(words[2]);
	cylinder->height = parse_radius(words[3]);
	cylinder->option = parse_option(words[4]);
	if (cylinder->option == 0 || cylinder->option == 1)
		cylinder->rgb = parse_rgb(words[5]);
	else if (cylinder->option == 2)
	{
		n = parse_option(words[5]);
		cylinder->texture = get_texture(vars, n);
	}
	return (cylinder);
}

t_circle	*parse_circle(t_vars *vars, char **words)
{
	t_circle	*circle;
	int			n;

	if (ft_strlen2(words) < 5)
		parse_error();
	circle = (t_circle *)malloc(sizeof(t_circle));
	circle->point = parse_point(words[0]);
	circle->ov = parse_ov(words[1]);
	circle->or = vector_unit(vector_set_def(circle->ov));
	circle->oc = vector_unit(vector_outer_product(circle->ov, circle->or));
	circle->radius = parse_radius(words[2]);
	circle->option = parse_option(words[3]);
	if (circle->option == 0 || circle->option == 1)
		circle->rgb = parse_rgb(words[4]);
	else if (circle->option == 2)
	{
		n = parse_option(words[4]);
		circle->texture = get_texture(vars, n);
	}
	else
		parse_error();
	return (circle);
}

t_cone	*parse_cone(t_vars *vars, char **words)
{
	t_cone	*cone;
	int		n;

	if (ft_strlen2(words) < 6)
		parse_error();
	cone = (t_cone *)malloc(sizeof(t_cone));
	cone->point = parse_point(words[0]);
	cone->ov = parse_ov(words[1]);
	cone->or = vector_unit(vector_set_def(cone->ov));
	cone->degree = parse_degree(words[2]);
	cone->height = parse_radius(words[3]);
	cone->option = parse_option(words[4]);
	if (cone->option == 0 || cone->option == 1)
		cone->rgb = parse_rgb(words[5]);
	else if (cone->option == 2)
	{
		n = parse_option(words[5]);
		cone->texture = get_texture(vars, n);
	}
	return (cone);
}
