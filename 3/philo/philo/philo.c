/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:22:10 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 13:57:20 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starving(t_beggar *beggar)
{
	long		now;

	now = time_now() - beggar->st;
	if (now - beggar->last_eat > beggar->time_to_die)
	{
		pthread_mutex_lock(beggar->dead_mutex);
		if (*(beggar->dead))
		{
			pthread_mutex_unlock(beggar->dead_mutex);
			return (1);
		}
		*(beggar->dead) = 1;
		pthread_mutex_unlock(beggar->dead_mutex);
		printf("%ld %d %s\n", timestamp(beggar->st) / 1000, beggar->n, "died");
		return (1);
	}
	pthread_mutex_lock(beggar->dead_mutex);
	if (*(beggar->dead))
	{
		pthread_mutex_unlock(beggar->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(beggar->dead_mutex);
	return (0);
}

void	getting_left(t_beggar *beggar)
{
	pthread_mutex_lock(beggar->l_mutex);
	if (*(beggar->left_fork))
	{
		*(beggar->left_fork) = 0;
		pthread_mutex_unlock(beggar->l_mutex);
		print_string(beggar, "has taken a fork");
		beggar->left_hand = 1;
	}
	else
		pthread_mutex_unlock(beggar->l_mutex);
}

int	getting_right(t_beggar *beggar)
{
	pthread_mutex_lock(beggar->r_mutex);
	if (*(beggar->right_fork))
	{
		*(beggar->right_fork) = 0;
		pthread_mutex_unlock(beggar->r_mutex);
		print_string(beggar, "has taken a fork");
		beggar->right_hand = 1;
		return (1);
	}
	pthread_mutex_unlock(beggar->r_mutex);
	return (0);
}

int	eating(t_beggar *beggar)
{
	if (beggar->left_hand && beggar->right_hand)
	{
		beggar->last_eat = timestamp(beggar->st);
		print_string(beggar, "is eating");
		while_sleep(beggar->st, beggar->last_eat, beggar->time_to_eat);
		(beggar->eat_count) += 1;
		pthread_mutex_lock(beggar->l_mutex);
		pthread_mutex_lock(beggar->r_mutex);
		*(beggar->left_fork) = 1;
		*(beggar->right_fork) = 1;
		pthread_mutex_unlock(beggar->l_mutex);
		pthread_mutex_unlock(beggar->r_mutex);
		if (beggar->must_eat == beggar->eat_count)
			return (1);
		beggar->left_hand = 0;
		beggar->right_hand = 0;
		print_string(beggar, "is sleeping");
		while_sleep(beggar->st, timestamp(beggar->st), beggar->time_to_sleep);
		print_string(beggar, "is thinking");
	}
	return (0);
}
