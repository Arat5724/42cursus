# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 11:45:45 by jeongble          #+#    #+#              #
#    Updated: 2023/02/08 18:37:00 by jeongble         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = #-Wall -Wextra -Werror
NAME = push_swap
SRCS =  push_swap.c push_swap_parse.c push_swap_node.c push_swap_op.c \
		push_swap_op_node.c push_swap_stack.c push_swap_sort.c \
		push_swap_op1.c push_swap_op2.c push_swap_op3.c \
		ft_atoi_err.c \
		push_swap_queue.c \
		push_swap_queue_valid.c sort2.c op.c s.c
CHCKER = checker
B_SRCS = checker.c push_swap_parse.c push_swap_node.c push_swap_op.c \
		push_swap_op_node.c push_swap_stack.c push_swap_sort.c \
		push_swap_op1.c push_swap_op2.c push_swap_op3.c \
		ft_atoi_err.c \
		push_swap_queue.c \
		push_swap_queue_valid.c \
		get_next_line.c get_next_line_utils.c sort2.c op.c s.c
OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

all : $(NAME)

bonus : $(CHCKER)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(CHCKER) : $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $(CHCKER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS) $(B_OBJS)

fclean : clean
	rm -f $(NAME)
	rm -f $(CHCKER)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re