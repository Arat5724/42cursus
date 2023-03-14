/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:25:23 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 16:17:14 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_last(char **lst)
{
	char	*last;
	int		i;
	int		j;

	i = 0;
	while (*(lst + i))
		i ++;
	last = *(lst + i - 1);
	j = 0;
	while (j < i - 1)
	{
		free(*(lst + j));
		j ++;
	}
	free(lst);
	return (last);
}

char	*get_shell1(char **envp)
{
	static const char	set[3] = {'"', '/', 0};
	int					i;
	char				**temp;

	temp = 0;
	i = 0;
	while (*(envp + i))
	{
		if (!ft_memcmp("_=", *(envp + i), 2))
		{
			temp = ft_split_set(*(envp + i) + 2, set);
			break ;
		}
		i ++;
	}
	if (temp)
		return (get_last(temp));
	return (get_shell2(envp));
}

char	*get_shell2(char **envp)
{
	static const char	set[3] = {'"', '/', 0};
	int					i;
	char				**temp;

	temp = 0;
	i = 0;
	while (*(envp + i))
	{
		if (!ft_memcmp("SHELL=", *(envp + i), 6))
		{
			temp = ft_split_set(*(envp + i) + 6, set);
			break ;
		}
		i ++;
	}
	if (temp)
		return (get_last(temp));
	return (0);
}

char	*ft_pathjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (*(s1 + i) || *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
		i ++;
	}
	return (0);
}
