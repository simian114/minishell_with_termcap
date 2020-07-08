# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmoon <gmoon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/11 21:00:54 by gmoon             #+#    #+#              #
#    Updated: 2020/07/08 12:15:00 by sanam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./obj

SRC =	check_redirection.c	\
		init_shell.c		\
		cmd_switch.c		\
		convert_arg.c		\
		exec_line.c			\
		get_args.c			\
		main.c				\
		pipe.c				\
		print_art.c			\
		semicolon.c			\
		signal.c			\
		store_status.c		\
		util_env.c			\
		util_free.c			\
		util.c				\
		builtin/sh_cd.c		\
		builtin/sh_clear.c	\
		builtin/sh_echo.c	\
		builtin/sh_env.c	\
		builtin/sh_exec.c	\
		builtin/sh_export.c	\
		builtin/sh_ls.c		\
		builtin/sh_pwd.c	\
		builtin/sh_unset.c	\
		builtin/sh_exit.c	\

OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

FTDIR = ./libft
FT_LIB = $(addprefix $(FTDIR)/,libft.a)
FT_INC = -I $(FTDIR)
FT_LNK = -L $(FTDIR) -l ft -ltermcap

all: obj $(FT_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR) > /dev/null
	@mkdir -p $(OBJDIR)/builtin  > /dev/null

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@echo "Making FT library..."
	@make -C $(FTDIR) > /dev/null

$(NAME): $(OBJ)
	@echo "Making MINISHELL..."
	@$(CC) $(OBJ) $(FT_LNK) -o $(NAME)
	@echo "FIN! Now you can use MINISHELL!"

bonus: $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make -C $(FTDIR) clean > /dev/null

fclean: clean
	@rm -f $(NAME)
	@make -C $(FTDIR) fclean > /dev/null

re: fclean all

run	:
	@make
	@echo "Executing MINISHELL!"
	@./minishell
	@make fclean

val:
	@make
	@echo "Memory check using Valgrind!"
	@valgrind --leak-check=full ./minishell

.PHONY : all bonus clean fclean re run
