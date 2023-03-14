/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_wc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:49:26 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 11:50:55 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	ft_reverse_str(char *str)
{
	const int	len = ft_strlen(str);
	char		temp;
	int			i;

	i = 0;
	while (i < len / 2)
	{
		temp = *(str + i);
		*(str + i) = *(str + len - 1 - i);
		*(str + len - 1 - i) = temp;
		i ++;
	}
}

int	parse_wc_end2(char *word, char *filename)
{
	int		result;
	char	*word_dup;
	char	*file_dup;

	word_dup = ft_strdup(word);
	file_dup = ft_strdup(filename);
	ft_reverse_str(word_dup);
	ft_reverse_str(file_dup);
	if (ft_strnstr(file_dup, word_dup, ft_strlen(word_dup)))
		result = 1;
	else
		result = 0;
	free(word_dup);
	free(file_dup);
	return (result);
}

int	parse_wc_end(char *wc, const char **words,
	const int wordslen, char *filename)
{
	char	*temp;
	int		i;

	i = wordslen - 1;
	if (*(wc + ft_strlen(wc) - 1) == '*')
	{
		if (i == 0 && *(wc) != '*')
			temp = ft_strnstr(filename, *(words), ft_strlen(*(words)));
		else
			temp = ft_strnstr(filename, *(words + i), ft_strlen(filename));
		if (!temp)
			return (0);
		return (1);
	}
	else
		return (parse_wc_end2(*((char **)words + i), filename));
}

int	parse_wc_suetent(char *wc, const char **words,
	const int wordslen, char *filename)
{
	char		*temp;
	int			i;

	if (!wordslen)
		return (1);
	i = 0;
	while (i < wordslen - 1)
	{
		if (i == 0 && *(wc) != '*')
			temp = ft_strnstr(filename, *(words), ft_strlen(*(words)));
		else
			temp = ft_strnstr(filename, *(words + i), ft_strlen(filename));
		if (!temp)
			return (0);
		filename = temp + ft_strlen(*(words + i));
		i ++;
	}
	return (parse_wc_end(wc, words, wordslen, filename));
}

void	parse_wc_join(char **result, char *filename)
{
	int			prev_len;
	const int	file_len = ft_strlen(filename);
	char		*temp;

	if (!*(result))
		*(result) = ft_strdup(filename);
	else
	{
		prev_len = ft_strlen(*(result));
		temp = malloc(prev_len + file_len + 2);
		ft_memcpy(temp, *(result), prev_len);
		*(temp + prev_len) = ' ';
		ft_memcpy(temp + prev_len + 1, filename, file_len + 1);
		free(*(result));
		*(result) = temp;
	}
}
