/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:21:27 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 16:28:56 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_len
{
	char	buf[BUFFER_SIZE];
	ssize_t	success;
	size_t	sol;
	size_t	len;
	size_t	new;
}		t_info;

int		buf_end(char **str, t_info *info);
int		fd_error(int fd, char **str, t_info *info);
char	*get_next_line(int fd);
char	*buf_join(char **str, char *buffer, t_info *info, int option);
void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif