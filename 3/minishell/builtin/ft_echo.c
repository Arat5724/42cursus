/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:58:20 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/01 20:15:46 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

void	ft_echo(char **words)
{
	int		i;
	char	*w;
	char	nflag;

	close(0);
	nflag = 0;
	i = 1;
	while (*(words + i))
	{
		w = *(words + i);
		if (i == 1 && ft_strlen(w) == 2 && !ft_strncmp(w, "-n", 2))
			nflag = 1;
		else
		{
			ft_putstr_fd(w, 1);
			if (*(words + i + 1))
				ft_putstr_fd(" ", 1);
		}
		i ++;
	}
	if (!nflag)
		write(1, "\n", 1);
	close (1);
	exit(0);
}
