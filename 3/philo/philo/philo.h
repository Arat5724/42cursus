/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:59:42 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:41:33 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_arg
{
	int		number;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
}		t_arg;

typedef struct s_list
{
	long			st;
	struct s_arg	args;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	dead_mutex;
	char			*forks;
	char			dead;
}		t_list;

typedef struct s_beggar
{
	int				n;
	long			st;
	long			last_eat;
	char			left_hand;
	char			right_hand;
	char			*left_fork;
	char			*right_fork;
	char			*dead;
	pthread_mutex_t	*l_mutex;
	pthread_mutex_t	*r_mutex;
	pthread_mutex_t	*dead_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				eat_count;
}		t_beggar;

int		ft_atoi(const char *str);
void	while_sleep(long st, long before, long after);
long	timestamp(long st);
long	time_now(void);
void	print_string(t_beggar *beggar, const char *str);

void	list_init(t_list *list, char **argv);
void	beggar_init(t_beggar *beggar, int n, t_list *list);

void	*begging(void *data);
int		starving(t_beggar *beggar);
void	getting_left(t_beggar *beggar);
int		getting_right(t_beggar *beggar);
int		eating(t_beggar *beggar);
#endif