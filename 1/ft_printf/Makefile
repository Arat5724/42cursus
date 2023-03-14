CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
AR = ar
ARFLAGS = rc
INC = ./
HEADER = ft_printf.h
NAME = libftprintf.a
SRCS := ft_flag_utils.c ft_print_char.c ft_print_id.c \
		ft_print_p.c ft_print_s.c ft_print_u.c ft_print_utils.c \
		ft_print_x.c ft_print_x2.c ft_printf.c ft_utils.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

bonus : all

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -o $(<:.c=.o) $<

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re