/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:39:05 by jeongble          #+#    #+#             */
/*   Updated: 2023/02/09 12:05:32 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int get_span(int argc) {
  const int size = 2 * (argc - 1);
  int i;

  i = 0;
  while (i * i < size) i++;
  return (i);
}

void queue_play(t_queue **front, t_queue **back, t_op **result) {
  while (*(front)) queue_start(front, back, result, 0);
  op_print(*(result));
}

int main(int argc, char **argv) {
  t_stack *stack;
  t_stack *stack2;
  t_stack *kcats;
  t_stack *kcats2;
  t_queue *front;
  t_queue *back;
  t_op *result;
  t_ops *ops;
  t_ops *ops2;
  t_ops *spo;
  t_ops *spo2;
  clock_t start;
  clock_t end;
  int *s;
  int *s_inv;
  t_stack *id;
  int i;
  int len;

  start = clock();
  ops = ops_new();
  ops2 = ops_new();
  spo = ops_new();
  spo2 = ops_new();
  len = argc - 1;
  s = ft_parse(len, argv + 1);
  s_inv = fun_inverse(s, len);

  if (s) {
    stack = stack_init(s, len);
    if (argc > 7) {
      stack2 = stack_init(s, len);
      kcats = stack_init(s_inv, len);
      kcats2 = stack_init(s_inv, len);
      sort(stack, len, get_span(len), ops);
      sort2(stack2, len, get_span(len), ops2);
      sort(kcats, len, get_span(len), spo);
      sort2(kcats2, len, get_span(len), spo2);
      ops_optimize(spo);
      ops_optimize(ops2);
      ops_optimize(ops);
      ops_optimize(spo2);

      if (ops->n <= ops2->n && ops->n <= spo->n && ops->n <= spo2->n) {
        ops_print(ops);
      } else if (ops2->n <= ops->n && ops2->n <= spo->n && ops2->n <= spo2->n) {
        ops_print(ops2);
      } else if (spo->n <= ops->n && spo->n <= ops2->n && spo->n <= spo2->n) {
        ops_reverse(spo);
        ops_print(spo);
      } else {
        ops_reverse(spo2);
        ops_print(spo2);
      }
    } else {
      result = 0;
      front = queue_new(stack, 0, 0, -1);
      back = front;
      queue_play(&front, &back, &result);
      return (0);
    }
  }
  stack_del(stack);
  end = clock();
  // printf("time = %f\n", (double)(end - start) / CLOCKS_PER_SEC);
  return (0);
}
