/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:09:13 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/25 12:09:20 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

typedef struct s_len
{
	char	buf[BUFFER_SIZE];
	ssize_t	success;
	size_t	sol;
	size_t	len;
	size_t	new;
}		t_info2;

int		buf_end(char **str, t_info2 *info);
int		fd_error(int fd, char **str, t_info2 *info);
char	*get_next_line(int fd);
char	*buf_join(char **str, char *buffer, t_info2 *info, int option);
void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif
