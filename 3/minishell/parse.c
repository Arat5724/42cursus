/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:55:07 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/02 08:18:23 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lmshell.h"

void	parse_1(t_token **head, char *str)
{
	char	*t_str;

	t_str = str;
	*(head) = parse_char(&t_str);
	free(str);
}

t_cmd	*parse_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (0);
}

t_cmd	*parse(char *str, int *exit_status)
{
	t_token		*head;
	char		**words;
	char		**temp;
	t_cmd		*result;

	parse_env(&str, *(exit_status));
	parse_wc(&str);
	parse_1(&head, str);
	if (!head)
	{
		*(exit_status) = 0;
		return (0);
	}
	words = join_token(head);
	free_token(head);
	temp = words;
	result = parse_cmds(&temp);
	free2(words);
	if (!result)
	{
		*(exit_status) = 258;
		return (parse_error("syntax error!"));
	}
	return (result);
}
