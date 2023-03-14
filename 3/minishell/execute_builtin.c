/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:28:57 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:33:20 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	execute_is_builtin(t_cmd *cmds, char *result, int size)
{
	static const char	*builtins[4] = {"cd", "unset", "exit", "export"};
	int					i;

	cmds->is_builtin = 0;
	if (!result)
		return ;
	i = 0;
	while (i < 3)
	{
		if (ft_strlen(result) == ft_strlen(builtins[i])
			&& !ft_strncmp(result, builtins[i], ft_strlen(builtins[i])))
			cmds->is_builtin = 1;
		i ++;
	}
	if (ft_strlen(result) == ft_strlen(builtins[i])
		&& !ft_strncmp(result, builtins[i], ft_strlen(builtins[i]))
		&& size != 1)
		cmds->is_builtin = 1;
}

int	execute_builtin_cmd(t_cmd *cmds, char **words, int *exit_status)
{
	static const char	*builtins[4] = {"cd", "unset", "exit", "export"};
	static void (*const	builtin_cmd[4])(char **words, int *exit_status) = {
		ft_cd, ft_unset, ft_exit, ft_export1};
	int					i;

	if (cmds->is_builtin)
	{
		i = 0;
		while (i < 4)
		{
			if (ft_strlen(*(words)) == ft_strlen(builtins[i])
				&& !ft_strncmp(*(words), builtins[i], ft_strlen(builtins[i])))
			{
				(builtin_cmd[i])(words, exit_status);
				break ;
			}
			i ++;
		}
		return (0);
	}
	else
		return (1);
}

void	execute_child_builtin(char **words)
{
	static const char	*builtins[4] = {"echo", "pwd", "export", "env"};
	static void (*const	builtin_cmd[4])(char **words) = {
		ft_echo, ft_pwd, ft_export2, ft_env};
	int					i;

	i = 0;
	while (i < 4)
	{
		if (ft_strlen(*(words)) == ft_strlen(builtins[i])
			&& !ft_strncmp(*(words), builtins[i], ft_strlen(builtins[i])))
		{
			(builtin_cmd[i])(words);
		}
		i ++;
	}
}
