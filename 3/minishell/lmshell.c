/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:00:17 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:23:23 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

char	**g_envp;

void	handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	words_size(char **words)
{
	int	i;

	i = 0;
	while (*(words + i))
		i ++;
	return (i);
}

char	**copy_envp(char **first_envp)
{
	const int	size = words_size(first_envp);
	char		**result;
	int			i;

	result = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		*(result + i) = ft_strdup(*(first_envp + i));
		i ++;
	}
	*(result + i) = 0;
	return (result);
}

int	main(int argc, char **argv, char **first_envp)
{
	char	*str;
	t_cmd	*cmd_tree;
	int		exit_status;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	exit_status = 0;
	g_envp = copy_envp(first_envp);
	while (1)
	{
		signal(SIGINT, handler);
		str = readline("lmsh-0.1 > ");
		if (!str)
			exit(255);
		add_history(str);
		cmd_tree = parse(str, &exit_status);
		if (cmd_tree)
			execute_head(cmd_tree, &exit_status);
		free_cmds(cmd_tree);
	}
	return (0);
}
