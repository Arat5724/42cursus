/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:40:37 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 07:50:54 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_num	*node_new(int n)
{
	t_num	*result;

	result = (t_num *)malloc(sizeof(t_num));
	result->next = 0;
	result->last = 0;
	result->n = n;
	return (result);
}

void	node_dup(t_num **dst, t_num **dst_tail, t_num *src)
{
	t_num	*result;
	t_num	*tail;
	t_num	*temp;

	result = 0;
	tail = 0;
	while (src)
	{
		temp = node_new(src->n);
		if (result)
		{
			tail->next = temp;
			temp->last = tail;
		}
		else
			result = temp;
		tail = temp;
		src = src->next;
	}
	*(dst) = result;
	*(dst_tail) = tail;
}

void	node_clear(t_num **stack)
{
	t_num	*next;

	if (!*(stack))
		return ;
	while (*(stack))
	{
		next = (*(stack))->next;
		(*(stack))->next = 0;
		(*(stack))->last = 0;
		(*(stack))->n = 0;
		free(*(stack));
		*(stack) = next;
	}
}

int	node_issort(t_num *stack)
{
	int		now;
	int		last;

	last = stack->n;
	stack = stack->next;
	while (stack)
	{
		now = stack->n;
		if (last > now)
			return (0);
		last = now;
		stack = stack->next;
	}
	return (1);
}
