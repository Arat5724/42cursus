/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:47:50 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:09:27 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

static void	print_error(char *dir)
{
	char	*msg;

	msg = strerror(errno);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(dir, 2);
}

static void	ft_chdir(char *dir, int *exit_status)
{
	int		re;
	char	*new_pwd;
	char	**words;

	re = chdir(dir);
	if (re == -1)
	{
		print_error(dir);
		*(exit_status) = 1;
	}
	else
	{
		new_pwd = ft_strjoin("PWD=", dir);
		words = (char **)malloc(sizeof(char *) * 3);
		*(words) = ft_strdup("export");
		*(words + 1) = new_pwd;
		*(words + 2) = 0;
		ft_export1(words, exit_status);
		free2(words);
		*(exit_status) = 0;
	}
}

void	ft_cd(char **words, int *exit_status)
{
	const int	size = ft_strlen2(words);

	if (size == 1)
		ft_chdir("/Users/jeongble", exit_status);
	else if (size == 2)
		ft_chdir(words[1], exit_status);
	else
	{
		ft_putstr_fd("cd: only one argument", 2);
		*(exit_status) = 1;
	}
}
