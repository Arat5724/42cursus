/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_wc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:37:17 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 12:29:58 by jeongble         ###   ########.fr       */
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
		if (c == g_set[i])
			return (i + 1);
		i ++;
	}
	return (0);
}

void	parse_wc_start(char *str, int *i)
{
	char	c;

	while (*(i) >= 0)
	{
		c = *(str + *(i));
		if (isset(c))
		{
			*(i) += 1;
			break ;
		}
		*(i) -= 1;
	}
	if (*(i) == -1)
		*(i) = 0;
}

int	wc_len(char *str)
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

char	*parse_wc_dir(char *wc)
{
	DIR				*dir_info;
	struct dirent	*dir_entry;
	char			*result;
	const char		**words = (const char **)ft_split(wc, '*');
	const int		wordslen = ft_strlen2((char **)words);

	result = 0;
	dir_info = opendir(".");
	if (dir_info)
	{
		dir_entry = readdir(dir_info);
		while (dir_entry)
		{
			if (parse_wc_suetent(wc, words, wordslen, dir_entry->d_name))
				parse_wc_join(&result, dir_entry->d_name);
			dir_entry = readdir(dir_info);
		}
		closedir(dir_info);
	}
	free(wc);
	free2((char **)words);
	return (result);
}

void	parse_wc(char **str)
{
	char	*insert;
	int		i;
	int		len;
	char	quote;

	i = -1;
	quote = 0;
	while (*(*(str) + (++i)))
	{
		if (!quote && (*(*(str) + i) == '\'' || *(*(str) + i) == '\"'))
			quote = *(*(str) + i);
		else if (*(*(str) + i) == quote)
			quote = 0;
		if (!quote && *(*(str) + i) == '*')
		{
			parse_wc_start(*(str), &i);
			len = wc_len(*(str) + i);
			insert = parse_wc_dir(ft_substr(*(str), i, len));
			if (insert)
				parse_env_insert(str, &i, len - 1, insert);
			else
				i += len;
			i --;
		}
	}
}
