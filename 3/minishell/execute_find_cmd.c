/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_find_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:38:10 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:35:18 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"
#include <sys/stat.h>
#include <stdbool.h>

char	**get_path_list(void)
{
	static const char	set[4] = {':', '=', '"', 0};
	int					i;
	char				**path_list;

	path_list = 0;
	i = 0;
	while (*(g_envp + i))
	{
		if (!ft_memcmp("PATH=", *(g_envp + i), 5))
		{
			path_list = ft_split_set(*(g_envp + i) + 5, set);
			break ;
		}
		i ++;
	}
	return (path_list);
}

char	*ft_pathjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
	if (!result)
		return (0);
	ft_memcpy(result, s1, sizeof(char) * len1);
	*(result + len1) = '/';
	ft_memcpy(result + len1 + 1, s2, sizeof(char) * (len2 + 1));
	return (result);
}

static bool	file_exists(char *filename)
{
	struct stat	buffer;

	return (stat(filename, &buffer) == 0);
}

void	find_cmd(char **cmd)
{
	int		i;
	char	*temp_path;
	char	**path_list;

	path_list = get_path_list();
	if (!path_list)
		return ;
	i = 0;
	while (*(path_list + i))
	{
		temp_path = ft_pathjoin(*(path_list + i), *(cmd));
		if (file_exists(temp_path))
		{
			free(*(cmd));
			*(cmd) = temp_path;
			free2(path_list);
			return ;
		}
		free(temp_path);
		i ++;
	}
	free2(path_list);
}
