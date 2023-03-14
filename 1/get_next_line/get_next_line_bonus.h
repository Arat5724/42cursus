/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:21:27 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/07 21:35:06 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_info
{
	struct s_info	*next;
	struct s_info	*last;
	int				fd;
	char			buf[BUFFER_SIZE];
	ssize_t			success;
	size_t			sol;
	size_t			len;
	size_t			new;
}		t_info;
void	fd_del(t_info *info);
int		buf_end(char **str, t_info *info);
int		fd_error(int fd, char **str, t_info *first, t_info **info);
t_info	*fd_new(int fd);
char	*get_next_line(int fd);
char	*buf_join(char **str, char *buffer, t_info *info, int option);
void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif