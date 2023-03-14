/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:45:28 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 15:40:11 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_list(char **lst)
{
	int		i;

	i = 0;
	while (*(lst + i))
	{
		free(*(lst + i));
		i ++;
	}
	free(lst);
}

char	**get_path_list(char **envp)
{
	static const char	set[4] = {':', '=', '"', 0};
	int					i;
	char				**path_list;

	path_list = 0;
	i = 0;
	while (*(envp + i))
	{
		if (!ft_memcmp("PATH=", *(envp + i), 5))
		{
			path_list = ft_split_set(*(envp + i), set);
			break ;
		}
		i ++;
	}
	free(path_list[0]);
	path_list[0] = get_shell1(envp);
	return (path_list);
}

char	**get_cmd_list(char *cmd_string, char **path_list)
{
	static const char	set[7] = {9, 10, 11, 12, 13, 32, 0};
	char				**cmd_list;
	char				*cmd;

	cmd_list = ft_split_set(cmd_string, set);
	cmd = find_cmd(cmd_list, path_list);
	free(cmd_list[0]);
	cmd_list[0] = cmd;
	return (cmd_list);
}

char	*find_cmd(char **cmd_list, char **path_list)
{
	int		i;
	char	*temp_path;
	int		access_code;

	i = 1;
	while (*(path_list + i))
	{
		temp_path = ft_pathjoin(*(path_list + i), *(cmd_list));
		access_code = access(temp_path, F_OK);
		if (!access_code)
			return (temp_path);
		free(temp_path);
		i ++;
	}
	return (ft_strdup(*(cmd_list)));
}
