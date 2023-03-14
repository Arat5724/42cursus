# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 13:13:19 by jeongble          #+#    #+#              #
#    Updated: 2022/08/02 12:37:33 by jeongble         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = lmsh
SRCS =  lmshell.c parse.c parse_split_word.c \
		parse_cmds.c parse_cmds2.c parse_struct_utils.c parse_struct_utils2.c \
		parse_expand_env.c parse_expand_wc.c parse_expand_wc2.c parse_join.c \
		parse_split_line.c parse_split_line2.c parse_split_line3.c parse_split_line_struct.c \
		execute.c execute_heredoc.c execute_find_cmd.c \
		execute_builtin.c execute_utils.c execute_utils2.c execute_redir.c \
		free_utils.c close_fd.c \
		get_next_line.c get_next_line_utils.c \
		builtin/ft_export.c builtin/ft_export_utils.c builtin/ft_cd.c \
		builtin/ft_unset.c builtin/ft_exit.c \
		builtin/ft_pwd.c builtin/ft_env.c builtin/ft_echo.c \
		strlen_utils.c
OBJS = $(SRCS:.c=.o)
LIBDIR = libft
LIBFT = $(LIBDIR)/libft.a
RLDIR = /Users/jeongble/goinfre/.brew/opt/readline/

all : $(NAME)

bonus : all

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBDIR) -lft -L$(RLDIR)lib -I$(RLDIR)include -lreadline -lhistory -o $(NAME)

$(LIBFT) :
	make -C $(LIBDIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(RLDIR)include -c $< -o $@

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