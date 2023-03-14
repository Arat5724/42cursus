/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:19:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 09:45:28 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_op *op_new(int op) {
  t_op *result;

  result = (t_op *)malloc(sizeof(t_op));
  result->next = NULL;
  result->last = NULL;
  result->op = op;
  return (result);
}

void op_clear(t_op **op) {
  t_op *next;

  if (!*(op)) return;
  while (*(op)) {
    next = (*(op))->next;
    (*(op))->next = 0;
    (*(op))->op = 0;
    free(*(op));
    *(op) = next;
  }
}

void op_dup(t_op **dst, t_op **dst_tail, t_op *src) {
  t_op *result;
  t_op *tail;
  t_op *temp;

  result = 0;
  tail = 0;
  while (src) {
    temp = op_new(src->op);
    if (result)
      tail->next = temp;
    else
      result = temp;
    tail = temp;
    src = src->next;
  }
  *(dst) = result;
  *(dst_tail) = tail;
}

void op_print(t_op *head) {
  static char *ops[11] = {"sa", "sb", "ss",  "pa",  "pb", "ra",
                          "rb", "rr", "rra", "rrb", "rrr"};
  t_op *next;

  while (head) {
    next = head->next;
    printf("%s\n", ops[head->op]);
    free(head);
    head = next;
  }
}

int op_size(t_op *head) {
  int i;

  i = 0;
  while (head) {
    i++;
    head = head->next;
  }
  return (i);
}
