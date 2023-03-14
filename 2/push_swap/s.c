#include "push_swap.h"

int apply_fun(int *s, t_stack *stack) {
  t_num *cur;

  cur = stack->stack_a;
  while (cur) {
    cur->n = s[cur->n];
    cur = cur->next;
  }
  cur = stack->stack_b;
  while (cur) {
    cur->n = s[cur->n];
    cur = cur->next;
  }
  return (0);
}

int apply_ops(t_ops *ops, t_stack *stack) {
  static int (*const op_fun[11])(t_stack * stack) = {sa, sb, ss,  pa,  pb, ra,
                                                     rb, rr, rra, rrb, rrr};
  t_op *op = ops->head;
  while (op) {
    op_fun[op->op](stack);
    op = op->next;
  }
  return (0);
}

int *fun_inverse(int *s, int len) {
  int *s_inverse;
  int i;

  s_inverse = malloc(sizeof(int) * len);
  i = 0;
  while (i < len) {
    s_inverse[s[i]] = i;
    i++;
  }
  return (s_inverse);
}