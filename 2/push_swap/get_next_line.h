/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:21:27 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/22 12:32:59 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_len
{
	char	buf[BUFFER_SIZE];
	ssize_t	rbyte;
	size_t	index;
	size_t	old_len;
	size_t	new_len;
}		t_info;

char	*get_next_line(int fd);
char	*buf_join(char **str, char *buffer, t_info *info);
#endif