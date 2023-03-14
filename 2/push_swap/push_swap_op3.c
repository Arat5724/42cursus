/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:03:31 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 07:47:34 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int rra(t_stack *stacks) {
  return (rrotate(&(stacks->stack_a), &(stacks->tail_a)));
}

int rrb(t_stack *stacks) {
  return (rrotate(&(stacks->stack_b), &(stacks->tail_b)));
}

int rrr(t_stack *stacks) { return (rra(stacks) || rrb(stacks)); }
