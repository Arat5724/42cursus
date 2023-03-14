# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 07:12:13 by jeongble          #+#    #+#              #
#    Updated: 2022/07/19 07:33:32 by jeongble         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = ./
HEADER = fractol.h
NAME = fractol
MLX = mlx/libmlx.a
SRCS = main.c mlx_hooks.c mlx_utils.c sets.c sets2.c utils.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

bonus : all

$(NAME) : $(MLX) $(OBJS)
	$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -O3 -o $(NAME)

$(MLX) :
	make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@

clean :
	make clean -C mlx
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make re -C mlx
	make fclean
	make all

.PHONY: all bonus clean fclean re
