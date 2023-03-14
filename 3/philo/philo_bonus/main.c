/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:17:18 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:39:58 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	begging(sem_t *forks, sem_t *dead, int n, t_arg *args)
{
	pthread_t	p_thread;
	t_starving	s_tarv;
	sem_t		*lasting;

	args->n = n;
	lasting = making_lasting(n);
	initing(&s_tarv, dead, args, lasting);
	pthread_create(&p_thread, 0, starving, &s_tarv);
	pthread_detach(p_thread);
	while (1)
	{
		eating(forks, lasting, args, &s_tarv);
		finishing(s_tarv.eat_count, args->must_eat, lasting);
		printf("%ld %d is sleeping\n", timestamp(args->st) / 1000, n);
		while_sleep(args->st, timestamp(args->st), args->time_to_sleep);
		printf("%ld %d is thinking\n", timestamp(args->st) / 1000, n);
	}
}

int	main(int argc, char **argv)
{
	sem_t	*forks;
	sem_t	*dead;
	t_arg	args;
	pid_t	*pids;
	int		i;

	if (!(argc == 5 || argc == 6))
		return (1);
	args_init(&args, argv);
	pids = (pid_t *)malloc(sizeof(pid_t) * args.number);
	args.st = time_now();
	opening(&forks, &dead, args.number);
	i = 0;
	while (i < args.number)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			begging(forks, dead, i + 1, &args);
		i ++;
	}
	killing(pids, args.number);
	sem_close(forks);
	sem_close(dead);
	return (0);
}
