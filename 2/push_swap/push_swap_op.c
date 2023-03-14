/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:14:33 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/21 15:03:56 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int swap(t_num **stack, t_num **tail) {
  t_num *first;
  t_num *second;
  t_num *third;

  if (*(stack) && (*(stack))->next) {
    first = *(stack);
    second = (*(stack))->next;
    third = (*(stack))->next->next;
    first->last = second;
    first->next = third;
    second->last = 0;
    second->next = first;
    *(stack) = second;
    if (third)
      third->last = first;
    else
      *(tail) = first;
    return (0);
  }
  return (1);
}

int push(t_num **dst, t_num **dst_tail, t_num **src, t_num **src_tail) {
  t_num *buf;

  if (*(src)) {
    buf = *(src);
    if ((*(src))->next) {
      *(src) = (*(src))->next;
      (*(src))->last = 0;
    } else {
      *(src) = 0;
      *(src_tail) = 0;
    }
    buf->next = *(dst);
    if (*(dst))
      (*(dst))->last = buf;
    else
      *(dst_tail) = buf;
    *(dst) = buf;
    return (0);
  }
  return (1);
}

int rotate(t_num **stack, t_num **tail) {
  t_num *first;
  t_num *second;

  if (*(stack) && (*(stack))->next && (*(stack))->next) {
    first = *(stack);
    second = first->next;
    second->last = 0;
    *(stack) = second;
    (*(tail))->next = first;
    first->last = *(tail);
    first->next = 0;
    *(tail) = first;
    return (0);
  }
  return (1);
}

int rrotate(t_num **stack, t_num **tail) {
  t_num *now_tail;
  t_num *last_tail;

  if (*(stack) && (*(stack))->next && (*(stack))->next) {
    now_tail = *(tail);
    last_tail = now_tail->last;
    last_tail->next = 0;
    now_tail->last = 0;
    *(tail) = last_tail;
    (*(stack))->last = now_tail;
    now_tail->next = *(stack);
    *(stack) = now_tail;
    return (0);
  }
  return (1);
}
