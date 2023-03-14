/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:00:13 by jeongble          #+#    #+#             */
/*   Updated: 2022/07/22 10:16:28 by jeongble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "get_next_line.h"

static int (*const	g_ops[11])(t_stack *stacks) = {
	sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr
};

static const char	*g_ops_char[11] = {
	"sa\n", "sb\n", "ss\n", "pa\n", "pb\n",
	"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"
};

static void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (*(s + i))
		i ++;
	write(fd, s, i);
	write(fd, "\n", 1);
}

static int	ft_parsec(int argc, char **argv, t_num **stack_a, t_num **tail)
{
	int	i;
	int	n;

	i = 1;
	while (i < argc)
	{
		n = ft_atoi_err(argv[i], stack_a, tail);
		if (n)
			return (1);
		i ++;
	}
	return (0);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) != *(s2 + i))
			return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
		i ++;
	}
	return (0);
}

static int	checking(t_stack *stack)
{
	char	*str;
	int		i;

	while (1)
	{
		str = get_next_line(0);
		if (!str)
			return (0);
		i = 0;
		while (i < 11)
		{
			if (!ft_strncmp(str, g_ops_char[i], strlen(g_ops_char[i])))
			{
				(g_ops[i])(stack);
				break ;
			}
			i ++;
		}
		if (i == 11)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*stack;

	if (argc == 1)
		return (1);
	stack = stack_init();
	if (!ft_parsec(argc, argv, &(stack->stack_a), &(stack->tail_a)))
	{
		if (!checking(stack))
		{
			if (!(stack->stack_b) && node_issort(stack->stack_a))
				ft_putendl_fd("OK", 1);
			else
				ft_putendl_fd("KO", 2);
		}
		else
			ft_putendl_fd("ERROR", 2);
	}
	else
		ft_putendl_fd("ERROR", 2);
	stack_del(stack);
	return (0);
}
