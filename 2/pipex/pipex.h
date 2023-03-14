/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 09:20:28 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/20 17:26:10 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define  PIPEX_H

# include "get_next_line.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define FIRST 1
# define LAST -1
# define MIDDLE 0

char	**ft_split_set(char const *s, char const *set);
void	free_list(char **lst);
char	*get_pwd(char **envp);
char	**get_path_list(char **envp);
char	**get_cmd_list(char *cmd_string, char **path_list);
char	*find_cmd(char **cmd_list, char **path_list);

void	switch_fd(int *fd, int *fd2, int status);
char	*ft_pathjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);

char	*get_last(char **lst);
char	*get_shell1(char **envp);
char	*get_shell2(char **envp);

void	child_process(int *fd, int *fd2, int status, char **cmd_list);

void	first_cmd(int *fd, int count, char **argv, char **path_list);
void	middle_cmd(int *fd, int count, char **argv, char **path_list);
void	last_cmd(int *fd, char **argv, char **path_list);

void	first_bonus_cmd(int *fd, int count, char **argv, char **path_list);
void	middle_bonus_cmd(int *fd, int count, char **argv, char **path_list);
void	last_bonus_cmd(int *fd, char **argv, char **path_list);

int		ft_pipe(int *fd);
int		ft_fork(void);
int		ft_open1(const char *filename, int option);
int		ft_open2(const char *filename, int option1, int option2);
int		ft_close(int fd);
int		ft_dup2(int fd1, int fd2);
int		ft_write(int fd, char *buffer, int size);
void	ft_cmd_not_found(char *cmd, char **path_list);

#endif