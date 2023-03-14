/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:59:38 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 07:47:25 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ra(t_stack *stacks)
{
	return (rotate(&(stacks->stack_a), &(stacks->tail_a)));
}

int	rb(t_stack *stacks)
{
	return (rotate(&(stacks->stack_b), &(stacks->tail_b)));
}

int	rr(t_stack *stacks)
{
	return (ra(stacks) || rb(stacks));
}
