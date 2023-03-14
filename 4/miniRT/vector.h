/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:41:35 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/12 13:30:42 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	vector_init(double x, double y, double z);
double		vector_size(t_vector vec);
double		vector_size2(t_vector vec);
t_vector	vector_unit(t_vector vec);
t_vector	vector_set_scale(t_vector vec, double scale);

double		vector_inner_product(t_vector a, t_vector b);
t_vector	vector_outer_product(t_vector a, t_vector b);
t_vector	vector_plus(t_vector a, t_vector b);
t_vector	vector_minus(t_vector a, t_vector b);
t_vector	vector_mul(t_vector vec, double d);

t_vector	vector_set_def(t_vector ov);
#endif