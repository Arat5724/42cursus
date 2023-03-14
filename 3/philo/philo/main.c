/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:51 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/04 22:44:53 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_list			list;
	t_beggar		**beggars;
	pthread_t		*p_thread;
	int				i;

	if (!(argc == 5 || argc == 6))
		return (1);
	list_init(&list, argv);
	beggars = (t_beggar **)malloc(sizeof(t_beggar *) * list.args.number);
	p_thread = (pthread_t *)malloc(sizeof(pthread_t) * list.args.number);
	i = 0;
	while (i < list.args.number)
	{
		*(beggars + i) = (t_beggar *)malloc(sizeof(t_beggar));
		beggar_init(*(beggars + i), i + 1, &list);
		pthread_create(p_thread + i, 0, begging, *(beggars + i));
		i ++;
	}
	i = -1;
	while (++i < list.args.number)
		pthread_join(*(p_thread + i), 0);
	return (0);
}

void	*begging(void *data)
{
	t_beggar	*beggar;

	beggar = (t_beggar *)data;
	if (!(beggar->n % 2))
		usleep(1000);
	while (1)
	{
		if (starving(beggar))
			break ;
		if (!beggar->left_hand)
			getting_left(beggar);
		if (beggar->left_hand)
		{
			if (getting_right(beggar))
			{
				if (eating(beggar))
					break ;
			}
		}
	}
	return (0);
}
