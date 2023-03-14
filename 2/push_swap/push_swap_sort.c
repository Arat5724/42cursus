/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 23:02:50 by jeongble          #+#    #+#             */
/*   Updated: 2023/02/09 12:10:55 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void sort23(t_stack *stack, int len, t_ops *ops);
static int sort_b(t_stack *stack, int len, t_ops *ops);

static int rai(t_stack *stack, int i, t_ops *ops) {
  int j;

  j = 0;
  while (j < i) {
    ra(stack);
    ops_push_back(ops, RA);
    j++;
  }
  return (1);
}

static int rrai(t_stack *stack, int i, t_ops *ops) {
  int j;

  j = 0;
  while (j < i) {
    rra(stack);
    ops_push_back(ops, RRA);
    j++;
  }
  return (1);
}

static int rrai22(t_stack *stack, int i) {
  int j;

  j = 0;
  while (j < i) {
    rra(stack);
    j++;
  }
  return (1);
}

int getspan2(int argc) {
  const int size = 2 * argc;
  int i;

  i = 0;
  while (i * i < size) i++;
  return (i);
}

int raorrra(t_stack *stack, int ispan, int len) {
  t_num *head;
  t_num *tail;
  int i;
  int h1;
  int h2;
  int t;

  head = stack->stack_a;
  if (!head || head->n <= ispan) {
    return (0);
  }
  head = head->next;
  tail = stack->tail_a;
  t = 0;
  i = 0;
  while (i < len / 3) {
    if (tail->n <= ispan) t++;
    i++;
    tail = tail->last;
  }
  h1 = 0;
  i = 0;
  while (i < len / 3) {
    if (head->n <= ispan) h1++;
    i++;
    head = head->next;
  }
  h2 = 0;
  while (i < len * 2 / 3) {
    if (head->n <= ispan) h2++;
    i++;
    head = head->next;
  }
  if (h1 + h2 < t) return (1);
  return (0);
}

void sort(t_stack *stack, int len, int span, t_ops *ops) {
  int i;
  int x;
  int q;
  int r;
  int rr;

  x = 1;
  r = 0;
  rr = 0;
  i = 0;
  q = span / 4 + 1;
  span *= 2;
  if (raorrra(stack, i + span, len - i)) rrai(stack, (len - i) / 3, ops);
  while (stack->stack_a) {
    if (stack->stack_a->n <= i) {
      if (i == rr) rr = 0;
      while (rr) {
        if (!rb(stack))
          if (x) ops_push_back(ops, RB);
        rr--;
      }
      if (stack->stack_b && stack->stack_b->n > stack->stack_a->n) {
        if (!rb(stack))
          if (x) ops_push_back(ops, RB);
        if (!pb(stack))
          if (x) ops_push_back(ops, PB);
        if (!rrb(stack))
          if (x) ops_push_back(ops, RRB);
      } else {
        if (!pb(stack))
          if (x) ops_push_back(ops, PB);
      };
      i++;
      if (i % q == 0 && span > 1) span -= 1;
      if (raorrra(stack, i + span, len - i)) rrai(stack, (len - i) / 3, ops);
    } else if (stack->stack_a->n <= i + span) {
      while (rr && stack->stack_b->n < stack->stack_a->n) {
        if (!rb(stack))
          if (x) ops_push_back(ops, RB);
        rr--;
      }
      if (!pb(stack))
        if (x) ops_push_back(ops, PB);
      rr++;
      i++;
      if (i % q == 0 && span > 1) span -= 1;
      if (raorrra(stack, i + span, len - i)) {
        rrai(stack, (len - i) / 3, ops);
      }
    } else {
      if (!ra(stack))
        if (x) ops_push_back(ops, RA);
    }
  }
  btoa(stack, len, ops);
}

void sort2(t_stack *stack, int len, int span, t_ops *ops) {
  int i;
  int x;
  int q;
  int r;
  int rr;

  x = 1;
  r = 0;
  rr = 0;
  i = 0;
  q = span / 4 + 1;
  span *= 2;
  if (raorrra(stack, i + span, len - i)) rrai(stack, (len - i) / 3, ops);
  while (stack->stack_a) {
    if (stack->stack_a->n <= i) {
      while (rr && stack->stack_b->n < stack->stack_a->n) {
        if (!rb(stack))
          if (x) ops_push_back(ops, RB);
        rr--;
      }
      if (!pb(stack))
        if (x) ops_push_back(ops, PB);
      rr++;
      i++;
      if (i % q == 0 && span > 1) span -= 1;
      if (raorrra(stack, i + span, len - i)) rrai(stack, (len - i) / 3, ops);
    } else if (stack->stack_a->n <= i + span) {
      if (i == rr) rr = 0;
      while (rr) {
        if (!rb(stack))
          if (x) ops_push_back(ops, RB);
        rr--;
      }
      if (stack->stack_b != NULL && stack->stack_b->n > stack->stack_a->n) {
        if (!rb(stack))
          if (x) ops_push_back(ops, RB);
        if (!pb(stack))
          if (x) ops_push_back(ops, PB);
        if (!rrb(stack))
          if (x) ops_push_back(ops, RRB);
      } else {
        if (!pb(stack))
          if (x) ops_push_back(ops, PB);
      };
      i++;
      if (i % q == 0 && span > 1) span -= 1;
      if (raorrra(stack, i + span, len - i)) rrai(stack, (len - i) / 3, ops);
    } else {
      if (!ra(stack))
        if (x) ops_push_back(ops, RA);
    }
  }
  btoa(stack, len, ops);
}

int rbi2(t_stack *stack, int i) {
  int j;

  j = 0;
  while (j < i) {
    rb(stack);
    j++;
  }
  return (i);
}

int rrbi2(t_stack *stack, int i) {
  int j;

  j = 0;
  while (j < i) {
    rrb(stack);
    j++;
  }
  return (i);
}

t_s *s_dup(t_s *src, int len, int size, int index) {
  t_s *result;
  int i;
  int j;

  result = malloc(sizeof(t_s));

  if (index >= 0)
    result->n = src->n + index;
  else {
    result->n = src->n - index;
    index += size;
  }

  result->stack_b = malloc(sizeof(int) * (size - 1));
  i = 0;
  while (i + index + 1 < size) {
    result->stack_b[i] = src->stack_b[i + index + 1];
    i++;
  }
  j = 0;
  while (i < size - 1) {
    result->stack_b[i] = src->stack_b[j];
    i++;
    j++;
  }

  result->inst = malloc(sizeof(int) * len);
  i = 0;
  while (i < len) {
    (result->inst)[i] = src->inst[i];
    i++;
  }
  return (result);
}

void s_del(t_s *s) {
  if (s) {
    free(s->stack_b);
    s->stack_b = NULL;

    free(s->inst);
    s->inst = NULL;
    free(s);
  }
}

int rbi(t_stack *stack, int i, t_ops *ops) {
  int j;

  j = 0;
  while (j < i) {
    rb(stack);
    ops_push_back(ops, RB);
    j++;
  }
  return (i);
}

int rrbi(t_stack *stack, int i, t_ops *ops) {
  int j;

  j = 0;
  while (j < i) {
    rrb(stack);
    ops_push_back(ops, RRB);
    j++;
  }
  return (i);
}

static int sort_b(t_stack *stack, int len, t_ops *ops) {
  t_num *head;
  t_num *tail;
  int i;

  head = stack->stack_b;
  tail = stack->tail_b;
  if (head->n == len) return (0);
  head = head->next;
  i = 1;
  while (head) {
    if (head->n == len) return (rbi(stack, i, ops));
    if (tail->n == len) return (rrbi(stack, i, ops));
    i++;
    head = head->next;
    tail = tail->last;
  }
  return (0);
}
