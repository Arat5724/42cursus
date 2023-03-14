/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:58:59 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:11:48 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

void	ft_export_add(char *word)
{
	const int	envp_size = ft_strlen2(g_envp);
	char		**result;
	int			i;

	result = malloc(sizeof(char *) * (envp_size + 2));
	i = 0;
	while (i < envp_size)
	{
		*(result + i) = ft_strdup(*(g_envp + i));
		i ++;
	}
	*(result + i) = ft_strdup(word);
	i ++;
	*(result + i) = 0;
	free2(g_envp);
	g_envp = result;
}

void	ft_export_kv(char *word, int key_size)
{
	char	*key;
	int		prev;

	key = ft_substr(word, 0, key_size);
	prev = ft_export_find_key(key, key_size);
	if (prev)
	{
		free(*(g_envp + prev - 1));
		*(g_envp + prev - 1) = ft_strdup(word);
	}
	else
		ft_export_add(word);
	free(key);
}

void	ft_export1(char **words, int *exit_status)
{
	char		*word;
	int			key_size;
	int			i;

	(void)exit_status;
	if (!*(words + 1))
	{
		close(0);
		ft_export_print();
		close(1);
		exit(0);
	}
	else
	{
		i = 1;
		while (*(words + i))
		{
			word = *(words + i);
			key_size = get_key_size(word);
			if (key_size != (int)ft_strlen(word))
				ft_export_kv(word, key_size);
			i ++;
		}
	}
}

void	ft_export2(char **words)
{
	(void)words;
	close(0);
	ft_export_print();
	close(1);
	exit(0);
}
