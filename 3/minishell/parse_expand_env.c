/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:37:58 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:47:00 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

static int	isset(char c)
{
	static const char	g_set[15] = {
		'<', '>', '|', '&', '(', ')', '\'', '\"', 9, 10, 11, 12, 13, 32, };
	int					i;

	if (!c)
		return (16);
	i = 0;
	while (i < 15)
	{
		if (c == g_set[i] || c == '$')
			return (i + 1);
		i ++;
	}
	return (0);
}

int	env_len(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (*(str + i))
	{
		c = *(str + i);
		if (isset(c))
			break ;
		i ++;
	}
	return (i);
}

char	*parse_env_g_envp(char *env, int len, int exit_status)
{
	int		i;
	char	*temp;
	char	*result;

	if (len == 1 && *(env) == '?')
		return (ft_itoa(exit_status));
	i = 0;
	while (*(g_envp + i))
	{
		temp = *(g_envp + i);
		if (!ft_memcmp(env, temp, len) && *(temp + len) == '=')
		{
			result = ft_substr(temp, len + 1, ft_strlen(temp) - len - 1);
			return (result);
		}
		i ++;
	}
	return (ft_strdup(""));
}

void	parse_env_insert(char **str, int *i, int len, char *insert)
{
	const int	insert_len = ft_strlen(insert);
	const int	prev_len = ft_strlen(*(str));
	const int	llen = prev_len - (len + 1) + insert_len;
	char		*new_str;

	new_str = malloc(llen + 1);
	ft_memcpy(new_str, *(str), *(i));
	ft_memcpy(new_str + *(i), insert, insert_len);
	ft_memcpy(
		new_str + *(i) + insert_len,
		*(str) + *(i) + len + 1,
		llen - (*(i) + insert_len) + 1);
	free(insert);
	free(*(str));
	*(str) = new_str;
	*(i) += insert_len;
}

void	parse_env(char **str, int exit_status)
{
	char	*insert;
	int		i;
	int		len;
	char	quote;

	i = 0;
	quote = 0;
	while (*(*(str) + i))
	{
		if (!quote && (*(*(str) + i) == '\'' || *(*(str) + i) == '\"'))
			quote = *(*(str) + i);
		else if (*(*(str) + i) == quote)
			quote = 0;
		if (*(*(str) + i) == '$' && quote != '\'')
		{
			len = env_len(*(str) + i + 1);
			if (len)
			{
				insert = parse_env_g_envp(*(str) + i + 1, len, exit_status);
				parse_env_insert(str, &i, len, insert);
				continue ;
			}
		}
		i ++;
	}
}
