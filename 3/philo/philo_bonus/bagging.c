/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bagging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:38:28 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:47:54 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*starving(void *data)
{
	t_starving	*s_tarv;
	sem_t		*lasting;
	long		time_to_die;
	long		*last_eat;
	long		st;

	s_tarv = (t_starving *)data;
	lasting = s_tarv->lasting;
	time_to_die = s_tarv->time_to_die;
	last_eat = &(s_tarv->last_eat);
	st = s_tarv->st;
	while (1)
	{
		sem_wait(lasting);
		if (timestamp(*(last_eat)) - st > time_to_die)
		{
			sem_wait(s_tarv->dead);
			printf("%ld %d %s\n", timestamp(st) / 1000, s_tarv->n, "died");
			sem_close(lasting);
			exit(1);
		}
		sem_post(lasting);
		usleep(50);
	}
	return (0);
}

sem_t	*making_lasting(int n)
{
	sem_t	*result;
	char	*name;

	name = ft_itoa(n);
	result = sem_open(name, O_CREAT, 0644, 1);
	sem_unlink(name);
	return (result);
}

void	initing(t_starving *s_tarv, sem_t *dead, t_arg *args, sem_t *lasting)
{
	s_tarv->last_eat = 0;
	s_tarv->dead = dead;
	s_tarv->lasting = lasting;
	s_tarv->st = args->st;
	s_tarv->eat_count = 0;
	s_tarv->time_to_die = args->time_to_die;
	s_tarv->n = args->n;
}

void	finishing(int eat_count, int must_eat, sem_t *lasting)
{
	if (eat_count == must_eat)
	{
		sem_close(lasting);
		exit(0);
	}
}

void	eating(sem_t *forks, sem_t *lasting, t_arg *args, t_starving *s_tarv)
{
	sem_wait(forks);
	printf("%ld %d has taken a fork\n", timestamp(args->st) / 1000, args->n);
	sem_wait(forks);
	printf("%ld %d has taken a fork\n", timestamp(args->st) / 1000, args->n);
	sem_wait(lasting);
	s_tarv->last_eat = timestamp(args->st);
	sem_post(lasting);
	printf("%ld %d is eating\n", timestamp(args->st) / 1000, args->n);
	while_sleep(args->st, timestamp(args->st), args->time_to_eat);
	s_tarv->eat_count += 1;
	sem_post(forks);
	sem_post(forks);
}
