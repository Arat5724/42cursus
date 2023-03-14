/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 09:35:21 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/19 00:52:30 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	arg_error(int argc, char *argv[], t_vars *vars)
{
	if (argc == 1)
		return (1);
	else
	{
		if (ft_strlen(argv[1]) == 1
			&& (argv[1][0] == '0' || argv[1][0] == '2'
			|| argv[1][0] == '3' || argv[1][0] == '1'))
		{
			vars->set = argv[1][0] - '0';
			return (0);
		}
		else
			return (1);
	}
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (arg_error(argc, argv, &vars))
		print_argument();
	else
	{
		if (vars.set == 1)
		{
			vars.julia.x = 0;
			vars.julia.y = 0;
			if (argc >= 3)
				vars.julia.x = ft_atod(argv[2]);
			if (argc >= 4)
				vars.julia.y = ft_atod(argv[3]);
		}
		mlx_start(&vars);
	}
	return (0);
}
