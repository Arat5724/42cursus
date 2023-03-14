/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 23:19:04 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 13:55:33 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	while ((9 <= *(str + i) && *(str + i) <= 13) || *(str + i) == ' ')
		i ++;
	sign = 1;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			sign = -1;
		i ++;
	}
	while (*(str + i) == '0')
		i ++;
	result = 0;
	while ('0' <= *(str + i) && *(str + i) <= '9')
	{
		result = result * 10 + (*(str + i) - '0') * sign;
		i ++;
	}
	return (result);
}

long	timestamp(long st)
{
	struct timeval	now_time;
	long			nt;

	gettimeofday(&now_time, 0);
	nt = now_time.tv_sec * 1000000 + now_time.tv_usec;
	return (nt - st);
}

void	while_sleep(long st, long before, long after)
{
	usleep(after * 0.8);
	while (timestamp(st) - before < after)
		usleep(500);
}

long	time_now(void)
{
	struct timeval	now_time;
	long			nt;

	gettimeofday(&now_time, 0);
	nt = now_time.tv_sec * 1000000 + now_time.tv_usec;
	return (nt);
}

void	print_string(t_beggar *beggar, const char *str)
{
	pthread_mutex_lock(beggar->dead_mutex);
	if (!*(beggar->dead))
		printf("%ld %d %s\n", timestamp(beggar->st) / 1000, beggar->n, str);
	pthread_mutex_unlock(beggar->dead_mutex);
}
