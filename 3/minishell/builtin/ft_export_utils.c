/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:10:46 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:11:11 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lmshell.h"

void	ft_export_print(void)
{
	int	i;

	i = 0;
	while (*(g_envp + i))
	{
		ft_putendl_fd(*(g_envp + i), 1);
		i ++;
	}
}

int	get_key_size(char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) != '=')
		i ++;
	if (*(str + i) == '=')
		i ++;
	return (i);
}

int	ft_export_find_key(char *key, int key_size)
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
