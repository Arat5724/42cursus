/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:39:56 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:41:35 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_arg
{
	int		number;
	int		n;
	long	st;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
}		t_arg;

typedef struct s_starving
{
	sem_t	*dead;
	sem_t	*lasting;
	long	st;
	long	last_eat;
	int		eat_count;
	long	time_to_die;
	int		n;
}		t_starving;

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	while_sleep(long st, long before, long after);
long	timestamp(long st);
long	time_now(void);

void	args_init(t_arg *args, char **argv);
void	opening(sem_t **forks, sem_t **dead, int number);
void	killing(pid_t *pids, int number);

void	*starving(void *data);
sem_t	*making_lasting(int n);
void	initing(t_starving *s_tarv, sem_t *dead, t_arg *args, sem_t *lasting);
void	finishing(int eat_count, int must_eat, sem_t *lasting);
void	eating(sem_t *forks, sem_t *lasting, t_arg *args, t_starving *s_tarv);

#endif