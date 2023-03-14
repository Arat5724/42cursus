/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:08:06 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 10:12:48 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

static int	words_size(char **words)
{
	int	i;

	i = 0;
	while (*(words + i))
		i ++;
	return (i);
}

int	ft_unset_find_key(char *key, int key_size)
{
	int	i;

	i = 0;
	while (*(g_envp + i))
	{
		if (!ft_memcmp(key, *(g_envp + i), key_size))
			return (i + 1);
		i ++;
	}
	return (0);
}

void	ft_unset_del(int key_index)
{
	const int	envp_size = words_size(g_envp);
	char		**result;
	int			i;
	int			j;

	key_index --;
	result = (char **)malloc(sizeof(char *) * envp_size);
	i = 0;
	j = 0;
	while (j < key_index)
	{
		*(result + i) = ft_strdup(*(g_envp + j));
		i ++;
		j ++;
	}
	j ++;
	while (j < envp_size)
	{
		*(result + i) = ft_strdup(*(g_envp + j));
		i ++;
		j ++;
	}
	*(result + i) = 0;
	free2(g_envp);
	g_envp = result;
}

void	ft_unset(char **words, int *exit_status)
{
	char	*word;
	int		i;
	int		key_index;

	(void)exit_status;
	i = 1;
	while (*(words + i))
	{
		word = *(words + i);
		key_index = ft_unset_find_key(word, ft_strlen(word));
		if (key_index)
			ft_unset_del(key_index);
		i ++;
	}
}
