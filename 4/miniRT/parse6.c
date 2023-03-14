/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 22:19:03 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 22:19:13 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

double	parse_ratio(char *str)
{
	double	ratio;

	ratio = ft_atod(str);
	if (!(0 < ratio && ratio < 1))
		parse_error();
	return (ratio);
}
