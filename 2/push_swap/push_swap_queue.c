/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_queue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:26:31 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 09:32:52 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int (*const	g_ops[11])(t_stack *stacks) = {
	sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr
};

t_queue	*queue_new(t_stack *stacks, t_op *head, t_op *tail, int last_op)
{
	t_queue	*result;

	result = (t_queue *)malloc(sizeof(t_queue));
	result->next = 0;
	result->stacks = stacks;
	result->head = head;
	result->tail = tail;
	result->last_op = last_op;
	return (result);
}

void	queue_del(t_queue **front)
{
	t_queue	*next;

	next = (*(front))->next;
	stack_del((*(front))->stacks);
	op_clear(&((*(front))->head));
	free(*(front));
	*(front) = next;
}

static void	queue_add_op(t_op **head, t_op **tail, int i)
{
	if (*(head))
	{
		(*(tail))->next = op_new(i);
		*(tail) = (*(tail))->next;
	}
	else
	{
		*(head) = op_new(i);
		*(tail) = *(head);
	}
}

static int	queue_issort(t_stack *stack_temp, t_op *op_temp, t_op **result)
{
	int		now;
	int		last;
	t_num	*stack;

	if (stack_temp->stack_b)
		return (0);
	stack = stack_temp->stack_a;
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
	*(result) = op_temp;
	stack_del(stack_temp);
	return (1);
}

void	queue_start(t_queue **front, t_queue **back, t_op **result, int n)
{
	int			i;
	t_stack		*stack_temp;
	t_op		*op_temp;
	t_op		*op_tail_temp;

	(void)n;
	i = -1;
	while (++i < 11 && !*(result))
	{
		if (!op_valid((*(front))->last_op, i))
			continue ;
		stack_temp = stack_dup((*(front))->stacks);
		if ((g_ops[i])(stack_temp))
			stack_del(stack_temp);
		else
		{
			op_dup(&op_temp, &op_tail_temp, (*(front))->head);
			queue_add_op(&op_temp, &op_tail_temp, i);
			if (queue_issort(stack_temp, op_temp, result))
				continue ;
			(*(back))->next = queue_new(stack_temp, op_temp, op_tail_temp, i);
			*(back) = (*(back))->next;
		}
	}
	queue_del(front);
}
