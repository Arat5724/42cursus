/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:52:14 by jeongble          #+#    #+#             */
/*   Updated: 2023/02/08 18:29:33 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack *stack_identity(int len) {
  t_stack *result;
  t_num *new;
  t_num *tail;
  int i;

  result = (t_stack *)malloc(sizeof(t_stack));

  tail = node_new(0);
  result->stack_a = tail;

  i = 1;
  while (i < len) {
    new = node_new(i);
    tail->next = new;
    new->last = tail;
    tail = new;
    i++;
  }

  result->tail_a = tail;
  result->stack_b = 0;
  result->tail_b = 0;
  return (result);
}

t_stack *stack_init(int *s, int len) {
  t_stack *result;
  t_num *new;
  t_num *tail;
  int i;

  result = (t_stack *)malloc(sizeof(t_stack));

  tail = node_new(s[0]);
  result->stack_a = tail;

  i = 1;
  while (i < len) {
    new = node_new(s[i]);
    tail->next = new;
    new->last = tail;
    tail = new;
    i++;
  }

  result->tail_a = tail;
  result->stack_b = 0;
  result->tail_b = 0;
  return (result);
}

void stack_del(t_stack *stacks) {
  node_clear(&(stacks->stack_a));
  node_clear(&(stacks->stack_b));
  free(stacks);
}

t_stack *stack_dup(t_stack *stacks) {
  t_stack *result;

  result = (t_stack *)malloc(sizeof(t_stack));
  node_dup(&(result->stack_a), &(result->tail_a), stacks->stack_a);
  node_dup(&(result->stack_b), &(result->tail_b), stacks->stack_b);
  return (result);
}

void stack_print(t_stack *stacks) {
  t_num *head;

  // printf("stack a\n");
  head = stacks->stack_a;
  while (head) {
    printf("%d ", head->n);
    head = head->next;
  }
  printf("\n");
  head = stacks->stack_b;
  while (head) {
    printf("%d ", head->n);
    head = head->next;
  }
  printf("\n");
}
