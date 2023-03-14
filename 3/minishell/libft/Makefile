# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 19:50:19 by jeongble          #+#    #+#              #
#    Updated: 2022/07/29 19:47:51 by jeongble         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
AR = ar
ARFLAGS = rc
INC = ./
HEADER = libft.h
NAME = libft.a
SRCS = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c \
	ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strdup.c\
	ft_strncmp.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
	ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memcmp.c ft_memchr.c \
	ft_atoi.c ft_itoa.c \
	ft_calloc.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c
BONUS_SRCS = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

ifdef BONUS
$(NAME) : $(OBJS) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(BONUS_OBJS)
else
$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
endif

%.o : %.c
	$(CC) $(CFLAGS) -o $(<:.c=.o) $<

bonus :
	make BONUS=1 all

clean :
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re