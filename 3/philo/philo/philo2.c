/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:32:36 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:37:52 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	beggar_init2(t_beggar *beggar, t_list *list)
{
	beggar->time_to_die = list->args.time_to_die;
	beggar->time_to_eat = list->args.time_to_eat;
	beggar->time_to_sleep = list->args.time_to_sleep;
	beggar->must_eat = list->args.must_eat;
	beggar->eat_count = 0;
}

void	beggar_init(t_beggar *beggar, int n, t_list *list)
{
	char			*left_fork;
	pthread_mutex_t	*l_mutex;

	beggar->n = n;
	beggar->st = list->st;
	beggar->last_eat = 0;
	beggar->left_hand = 0;
	beggar->right_hand = 0;
	left_fork = list->forks + n - 2;
	if (n == 1)
		left_fork = list->forks + list->args.number - 1;
	beggar->left_fork = left_fork;
	beggar->right_fork = list->forks + n - 1;
	beggar->dead = &(list->dead);
	l_mutex = list->fork_mutexes + beggar->n - 2;
	if (beggar->n == 1)
		l_mutex = list->fork_mutexes + list->args.number - 1;
	beggar->l_mutex = l_mutex;
	beggar->r_mutex = list->fork_mutexes + beggar->n - 1;
	beggar->dead_mutex = &(list->dead_mutex);
	beggar_init2(beggar, list);
}

void	args_init(t_arg *args, char **argv)
{
	args->number = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]) * 1000;
	args->time_to_eat = ft_atoi(argv[3]) * 1000;
	args->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (args->number <= 0 || args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		exit(1);
	args->must_eat = -1;
	if (argv[5])
	{
		args->must_eat = ft_atoi(argv[5]);
		if (args->must_eat <= 0)
			exit(1);
	}
}

void	list_init(t_list *list, char **argv)
{
	int				i;
	int				number;
	pthread_mutex_t	*fork_mutexes;

	list->st = timestamp(0);
	args_init(&(list->args), argv);
	number = (list->args).number;
	list->forks = (char *)malloc(sizeof(char) * number);
	memset(list->forks, 1, number);
	list->dead = 0;
	fork_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	list->fork_mutexes = fork_mutexes;
	i = -1;
	while (++i < number)
		pthread_mutex_init(fork_mutexes + i, 0);
	pthread_mutex_init(&(list->dead_mutex), 0);
}
