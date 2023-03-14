#include "push_swap.h"

t_ops *ops_new() {
  t_ops *new;

  new = malloc(sizeof(t_ops));
  new->head = NULL;
  new->tail = NULL;
  new->n = 0;
  return (new);
}

void ops_erase(t_ops *ops, t_op *op) {
  if (op->last) {
    op->last->next = op->next;
  } else {
    ops->head = op->next;
  }
  if (op->next) {
    op->next->last = op->last;
  } else {
    ops->tail = op->last;
  }
  free(op);
  ops->n -= 1;
}

static const int only_a[11] = {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0};

static const int only_b[11] = {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0};

static void (*const ops_[11])(t_ops *ops, int op) = {
    op_sa, op_sb, NULL, op_pa, op_pb, op_ra, op_rb, NULL, op_rra, op_rrb, NULL};

// static void (*const ops_[11])(t_ops *ops, int op) = {
//     op_sa, NULL, NULL, op_pa, op_pb, op_ra, op_rb, NULL, op_rra, op_rrb,
//     NULL};

void ops_push_back2(t_ops *ops, int op) {
  t_op *new;
  t_op *tail;

  new = op_new(op);
  if (ops->tail) {
    new->last = ops->tail;
    ops->tail->next = new;
  } else {
    ops->head = new;
  }
  ops->tail = new;
  ops->n += 1;
}

void ops_push_back(t_ops *ops, int op) {
  t_op *new;
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  if (ops->head && ops_[op]) {
    ops_[op](ops, op);
  } else {
    ops_push_back2(ops, op);
  }
}

void ops_insert_front(t_ops *ops, t_op *now, int op) {
  t_op *new;

  new = op_new(op);
  new->last = now->last;
  new->next = now;
  now->last = new;
  if (new->last) {
    new->last->next = new;
  } else {
    ops->head = new;
  }
  ops->n += 1;
}

void ops_insert_back(t_ops *ops, t_op *now, int op) {
  t_op *next;
  t_op *new;

  new = op_new(op);
  new->last = now;
  new->next = now->next;
  now->next = new;
  if (new->next) {
    new->next->last = new;
  } else {
    ops->tail = new;
  }
  ops->n += 1;
}

void op_sa(t_ops *ops, int op) {
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  while (tail && (only_b[tail->op] || tail->op == SA)) {
    if (tail->op == SA) target = tail;
    tail = tail->last;
  }
  if (target)
    ops_erase(ops, target);
  else if (ops->tail->op == SB)
    ops->tail->op = SS;
  else if (ops->tail->op == SS)
    ops->tail->op = SB;
  else
    ops_push_back2(ops, op);
}

void op_sb(t_ops *ops, int op) {
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  while (tail && (only_a[tail->op] || tail->op == SB)) {
    if (tail->op == SB) target = tail;
    tail = tail->last;
  }
  if (target)
    ops_erase(ops, target);
  else if (ops->tail->op == SA)
    ops->tail->op = SS;
  else if (ops->tail->op == SS)
    ops->tail->op = SA;
  else
    ops_push_back2(ops, op);
}

void op_pa(t_ops *ops, int op) {
  if (ops->tail->op == PB)
    ops_erase(ops, ops->tail);
  else
    ops_push_back2(ops, op);
}

void op_pb(t_ops *ops, int op) {
  if (ops->tail->op == PA)
    ops_erase(ops, ops->tail);
  else
    ops_push_back2(ops, op);
}

void op_ra(t_ops *ops, int op) {
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  while (tail && (only_b[tail->op] || tail->op == RRA)) {
    if (tail->op == RRA) target = tail;
    tail = tail->last;
  }
  if (target) {
    ops_erase(ops, target);
    return;
  }

  tail = ops->tail;
  while (tail && tail->op == RRB) {
    tail = tail->last;
  }
  if (tail && tail->op == RRR) {
    tail->op = RRB;
    return;
  }

  tail = ops->tail;
  target = NULL;
  while (tail && tail->op == RB) {
    target = tail;
    tail = tail->last;
  }
  if (target)
    target->op = RR;
  else if (ops->tail->op == RRR)
    ops->tail->op = RRB;
  else
    ops_push_back2(ops, op);
}

void op_rb(t_ops *ops, int op) {
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  while (tail && (only_a[tail->op] || tail->op == RRB)) {
    if (tail->op == RRB) target = tail;
    tail = tail->last;
  }
  if (target) {
    ops_erase(ops, target);
    return;
  }

  tail = ops->tail;
  while (tail && tail->op == RRA) {
    tail = tail->last;
  }
  if (tail && tail->op == RRR) {
    tail->op = RRA;
    return;
  }

  tail = ops->tail;
  target = NULL;
  while (tail && tail->op == RA) {
    target = tail;
    tail = tail->last;
  }
  if (target)
    target->op = RR;
  else if (ops->tail->op == RRR)
    ops->tail->op = RRA;
  else
    ops_push_back2(ops, op);
}

void op_rra(t_ops *ops, int op) {
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  while (tail && (only_b[tail->op] || tail->op == RA)) {
    if (tail->op == RA) target = tail;
    tail = tail->last;
  }
  if (target) {
    ops_erase(ops, target);
    return;
  }

  tail = ops->tail;
  while (tail && tail->op == RB) {
    tail = tail->last;
  }
  if (tail && tail->op == RR) {
    tail->op = RB;
    return;
  }

  tail = ops->tail;
  target = NULL;
  while (tail && tail->op == RRB) {
    target = tail;
    tail = tail->last;
  }
  if (target)
    target->op = RRR;
  else if (ops->tail->op == RR)
    ops->tail->op = RB;
  else
    ops_push_back2(ops, op);
}

void op_rrb(t_ops *ops, int op) {
  t_op *tail;
  t_op *target;

  tail = ops->tail;
  target = NULL;
  while (tail && (only_a[tail->op] || tail->op == RB)) {
    if (tail->op == RB) target = tail;
    tail = tail->last;
  }
  if (target) {
    ops_erase(ops, target);
    return;
  }

  tail = ops->tail;
  while (tail && tail->op == RA) {
    tail = tail->last;
  }
  if (tail && tail->op == RR) {
    tail->op = RA;
    return;
  }

  tail = ops->tail;
  target = NULL;
  while (tail && tail->op == RRA) {
    target = tail;
    tail = tail->last;
  }

  if (target)
    target->op = RRR;
  else if (ops->tail->op == RR)
    ops->tail->op = RA;
  else
    ops_push_back2(ops, op);
}

// RA
// PA
// RRA

// RA
// PB
// RRA

// RB
// PA
// RRB

// RB
// PB
// RRB

void ops_optimize(t_ops *ops) {
  t_op *now;
  t_op *last;
  t_op *next;

  now = ops->head;

  while (now) {
    if (now->op == PA || now->op == PB) {
      last = now->last;
      next = now->next;
      while (last && last->op == RR) last = last->last;
      while (next && next->op == RRR) next = next->next;
      if (last && next) {
        if (now->op == PA) {
          if (last->op == RA && next->op == RRA) {
            ops_erase(ops, last);
            ops_erase(ops, next);
            ops_insert_back(ops, now, SA);
          } else if (last->op == RB && next->op == RRB) {
            ops_erase(ops, last);
            ops_erase(ops, next);
            ops_insert_front(ops, now, SB);
          }
        } else {
          if (last->op == RA && next->op == RRA) {
            ops_erase(ops, last);
            ops_erase(ops, next);
            ops_insert_front(ops, now, SA);
          } else if (last->op == RB && next->op == RRB) {
            ops_erase(ops, last);
            ops_erase(ops, next);
            ops_insert_back(ops, now, SB);
          }
        }
      }
    }
    now = now->next;
  }
}

void ops_reverse(t_ops *spo) {
  t_op *head;
  int op;
  int *ops;
  int i;
  static const int rev_ops[11] = {SA,  SB,  SS, PB, PA, RRA,
                                  RRB, RRR, RA, RB, RR};

  ops = malloc(sizeof(int) * spo->n);
  head = spo->head;
  i = 0;
  while (head) {
    op = head->op;
    ops[i] = rev_ops[op];
    head = head->next;
    i++;
  }
  head = spo->head;
  i--;
  while (i >= 0) {
    head->op = ops[i];
    head = head->next;
    i--;
  }
}

void ops_print(t_ops *ops) {
  static char *insts[11] = {"sa", "sb", "ss",  "pa",  "pb", "ra",
                            "rb", "rr", "rra", "rrb", "rrr"};
  t_op *head;
  t_op *next;
  int i;

  i = 0;
  head = ops->head;
  while (head) {
    printf("%s\n", insts[head->op]);
    next = head->next;
    free(head);
    head = next;
  }
  // printf("%d\n", i);
}

void ops_free(t_ops *ops) {
  t_op *head;
  t_op *next;

  head = ops->head;
  while (head) {
    next = head->next;
    free(head);
    head = next;
  }
  free(ops);
  // printf("%d\n", i);
}

// void ops_push_back(t_ops *ops, int op) {
//   t_op *new;
//   t_op *tail;

//   tail = ops->tail;
//   if (ops->head) {
//     if (tail->op == SA && op == SB || tail->op == SB && op == SA) {
//       tail->op = SS;
//     } else if (tail->op == RA && op == RB) {
//       while (tail->last && tail->last->op == RA) tail = tail->last;
//       tail->op = RR;
//     } else if (tail->op == RB && op == RA) {
//       while (tail->last && tail->last->op == RB) tail = tail->last;
//       tail->op = RR;
//     } else if (tail->op == RRA && op == RRB || tail->op == RRB && op == RRA)
//     {
//       tail->op = RRR;
//     } else if (tail->op == SA && op == SS || tail->op == SS && op == SA) {
//       tail->op = SB;
//     } else if (tail->op == SB && op == SS || tail->op == SS && op == SB) {
//       tail->op = SA;
//     } else if (tail->op == RA && op == RRR || tail->op == RRR && op == RA) {
//       tail->op = RRB;
//     } else if (tail->op == RB && op == RRR || tail->op == RRR && op == RB) {
//       tail->op = RRA;
//     } else if (tail->op == RRA && op == RR || tail->op == RR && op == RRA) {
//       tail->op = RB;
//     } else if (tail->op == RRB && op == RR || tail->op == RR && op == RRB) {
//       tail->op = RA;
//     } else if (tail->op == RA && op == RRA || tail->op == RRA && op == RA ||
//                tail->op == RB && op == RRB || tail->op == RRB && op == RB ||
//                tail->op == SA && op == SA || tail->op == SB && op == SB ||
//                tail->op == RR && op == RRR || tail->op == RRR && op == RR ||
//                tail->op == PA && op == PB || tail->op == PB && op == PA) {
//       ops->tail = ops->tail->last;
//       free(tail);
//       if (ops->tail) {
//         ops->tail->next = NULL;
//       } else {
//         ops->head = NULL;
//       }
//       ops->n -= 1;
//     } else {
//       new = op_new(op);
//       tail->next = new;
//       new->last = tail;
//       ops->tail = new;
//       ops->n += 1;
//     }
//   } else {
//     new = op_new(op);
//     ops->head = new;
//     ops->tail = new;
//     ops->n += 1;
//   }
// }