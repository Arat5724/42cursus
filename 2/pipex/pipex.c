/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:40:43 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 17:21:37 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path_list;
	int		fd[2];

	path_list = get_path_list(envp);
	if (argc > 4)
	{
		if (!ft_strcmp("here_doc", argv[1]))
		{
			if (argc > 5)
				first_bonus_cmd(fd, argc, argv, path_list);
			else
				exit(1);
		}
		else
		{
			if (argc > 4)
				first_cmd(fd, argc, argv, path_list);
			else
				exit(1);
		}
	}
	free_list(path_list);
	return (0);
}
