/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:17:21 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/13 02:58:14 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_rgb	parse_rgb(char *str)
{
	char	**words;
	t_rgb	rgb;

	words = ft_split(str, ',');
	if (ft_strlen2(words) != 3)
		parse_error();
	rgb.r = (unsigned char)atoi(words[0]);
	rgb.g = (unsigned char)atoi(words[1]);
	rgb.b = (unsigned char)atoi(words[2]);
	ft_free2(words);
	return (rgb);
}

t_vector	parse_point(char *str)
{
	char		**words;
	t_vector	point;

	words = ft_split(str, ',');
	if (ft_strlen2(words) != 3)
		parse_error();
	point.x = ft_atod(words[0]);
	point.y = ft_atod(words[1]);
	point.z = ft_atod(words[2]);
	ft_free2(words);
	return (point);
}

t_vector	parse_ov(char *str)
{
	char		**words;
	t_vector	ov;

	words = ft_split(str, ',');
	if (ft_strlen2(words) != 3)
		parse_error();
	ov.x = ft_atod(words[0]);
	ov.y = ft_atod(words[1]);
	ov.z = ft_atod(words[2]);
	if (!(ov.x || ov.y || ov.z))
		parse_error();
	ft_free2(words);
	return (vector_unit(ov));
}

int	parse_degree(char *str)
{
	int	result;

	result = ft_atod(str);
	if (!(0 < result && result < 150))
		parse_error();
	return (result);
}

int	parse_wh(char *str)
{
	int	result;

	result = atoi(str);
	if (!(100 < result && result < 1201))
		parse_error();
	return (result);
}
