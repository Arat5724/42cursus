/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:48:54 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/01 20:14:23 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

void	ft_pwd(char **words)
{
	char	buf[255];

	(void)words;
	close(0);
	getcwd(buf, 255);
	ft_putendl_fd(buf, 1);
	close(1);
	exit(0);
}
