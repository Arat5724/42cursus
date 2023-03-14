/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:05:47 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 16:19:14 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

void	ft_exit(char **words, int *exit_status)
{
	if (ft_strlen2(words) > 2)
	{
		ft_putendl_fd("too many arg", 2);
		*(exit_status) = 1;
		return ;
	}
	(void)exit_status;
	ft_putstr_fd("exit\n", 1);
	if (*(words + 1))
		exit(ft_atoi(*(words + 1)));
	exit(0);
}
