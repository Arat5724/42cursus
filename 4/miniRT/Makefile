# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 07:12:13 by jeongble          #+#    #+#              #
#    Updated: 2022/08/12 23:36:10 by jeongble         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
INC = ./
NAME = miniRT
MLX = mlx/libmlx.a
SRCS = main.c put_pixels.c utils.c light.c \
		parse.c parse2.c parse3.c parse4.c parse5.c parse6.c \
		parse_utils.c parse_utils2.c \
		color1.c color2.c \
		circle.c circle_bump.c circle_check.c \
		cone1.c cone2.c cone_bump.c cone_check.c \
		cylinder.c cylinder_bump.c cylinder_check.c \
		plane.c plane_bump.c plane_check.c \
		sphere.c sphere_bump.c sphere_check.c \
		vector1.c vector2.c vector3.c \
		gnl/get_next_line.c gnl/get_next_line2.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

bonus : all

$(NAME) : $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -lz -framework OpenGL -framework AppKit -O3 -o $(NAME)

$(MLX) :
	make -C mlx

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re
