/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 22:34:56 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:37:38 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	opening(sem_t **forks, sem_t **dead, int number)
{
	*(forks) = sem_open("forks", O_CREAT, 0644, number);
	*(dead) = sem_open("dead", O_CREAT, 0644, 1);
	sem_unlink("forks");
	sem_unlink("dead");
}

void	killing(pid_t *pids, int number)
{
	int		j;
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WEXITSTATUS(status))
		{
			j = -1;
			while (++j < number)
			{
				if (pids[j])
					kill(pids[j], 9);
			}
			break ;
		}
	}
	while (waitpid(-1, &status, 0) != -1)
	{
	}
}
