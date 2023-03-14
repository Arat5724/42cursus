/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:49:16 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 10:40:21 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int ft_isvalid(char c1, char c2) {
  return ((c1 == '-' || c1 == '+') && '0' <= c2 && c2 <= '9');
}

static int ft_isdup(t_num *stack_a, int result) {
  while (stack_a) {
    if (stack_a->n == result) return (1);
    stack_a = stack_a->next;
  }
  return (0);
}

static void ft_getsign(int c1, int c2, int *i, int *sign) {
  if (ft_isvalid(c1, c2)) {
    if (c1 == '-')
      *(sign) = -1;
    else
      *(sign) = 1;
    *(i) = 1;
  } else {
    *(sign) = 1;
    *(i) = 0;
  }
}

void push_result(t_num **stack_a, t_num **tail, int result) {
  t_num *result_node;

  result_node = node_new(result);
  if (*(stack_a)) {
    (*(tail))->next = result_node;
    result_node->last = *(tail);
  } else
    *(stack_a) = result_node;
  *(tail) = result_node;
}

int ft_atoi_err(const char *str, t_num **stack_a, t_num **tail) {
  int i;
  int sign;
  long result;

  if (!*(str)) return (1);
  ft_getsign(*(str), *(str + 1), &i, &sign);
  result = 0;
  while ('0' <= *(str + i) && *(str + i) <= '9') {
    result = result * 10 + (*(str + i) - '0') * sign;
    if (result > I_MAX || result < I_MIN) return (1);
    i++;
  }
  if (*(str + i)) return (2);
  if (ft_isdup(*(stack_a), result)) return (3);
  push_result(stack_a, tail, result);
  return (0);
}
