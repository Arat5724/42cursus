/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:07:11 by jeongble          #+#    #+#             */
/*   Updated: 2023/02/08 17:59:42 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void pretty_n(int *arr, int *rra, t_stack *stack, t_stack *kcats);
static void get_size(t_num *last, t_num *next, int n, int *size);

static void ft_putendl_fd(char *s, int fd) {
  int i;

  i = 0;
  while (*(s + i)) i++;
  write(fd, s, i);
  write(fd, "\n", 1);
}

int ft_atoi(char *str) {
  int res;
  int sign;

  res = 0;
  sign = 1;
  while (*str == '-' || *str == '+') {
    if (*str == '-') {
      sign *= -1;
    }
    str++;
  }
  while ('0' <= *str && *str <= '9') {
    res = res * 10 + (*str - '0') * sign;
    str++;
  }
  return (res);
}

int *ft_parse(int len, char **argv) {
  int *arr;
  int *temp;
  int n;
  int issort;
  int i;
  int j;

  if (len == 1) return (NULL);
  temp = malloc(sizeof(int) * len);
  i = 0;
  while (i < len) {
    n = ft_atoi(argv[i]);
    j = 0;
    while (j < i) {
      if (temp[j] == n) {
        free(temp);
        return (NULL);
      }
      j++;
    }
    temp[i] = n;
    i++;
  }
  i = 0;
  while (++i < len)
    if (temp[i - 1] > temp[i]) break;

  if (i == len) {
    free(temp);
    return (NULL);
  }
  arr = malloc(sizeof(int) * len);
  i = 0;
  while (i < len) {
    n = 0;
    j = 0;
    while (j < len) {
      if (temp[j] < temp[i]) n++;
      j++;
    }
    arr[i] = n;
    i++;
  }
  free(temp);
  return (arr);
}
