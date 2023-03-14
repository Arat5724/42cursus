/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:51:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 07:47:19 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sa(t_stack *stacks)
{
	return (swap(&(stacks->stack_a), &(stacks->tail_a)));
}

int	sb(t_stack *stacks)
{
	return (swap(&(stacks->stack_b), &(stacks->tail_b)));
}

int	ss(t_stack *stacks)
{
	return (sa(stacks) || sb(stacks));
}

int	pa(t_stack *stacks)
{
	t_num	**dst;
	t_num	**dst_tail;
	t_num	**src;
	t_num	**src_tail;

	dst = &(stacks->stack_a);
	dst_tail = &(stacks->tail_a);
	src = &(stacks->stack_b);
	src_tail = &(stacks->tail_b);
	return (push(dst, dst_tail, src, src_tail));
}

int	pb(t_stack *stacks)
{
	t_num	**dst;
	t_num	**dst_tail;
	t_num	**src;
	t_num	**src_tail;

	dst = &(stacks->stack_b);
	dst_tail = &(stacks->tail_b);
	src = &(stacks->stack_a);
	src_tail = &(stacks->tail_a);
	return (push(dst, dst_tail, src, src_tail));
}
