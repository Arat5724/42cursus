# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 11:56:25 by jeongble          #+#    #+#              #
#    Updated: 2022/07/20 17:29:25 by jeongble         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRCS =  pipex.c pipex_men_cmd.c pipex_bonus_cmd.c \
		pipex_utils.c pipex_utils2.c ft_split_set.c \
		pipex_ex.c pipex_ex2.c \
		get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
LIBDIR = libft
LIBFT = $(LIBDIR)/libft.a

all : $(NAME)

bonus : all

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBDIR) -lft -o $(NAME)

$(LIBFT) :
	make -C $(LIBDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C $(LIBDIR)
	rm -f $(OBJS)

fclean : clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re