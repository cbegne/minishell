# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbegne <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/15 19:07:44 by cbegne            #+#    #+#              #
#    Updated: 2017/03/06 15:06:27 by cbegne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_NAME =	main.c\
			build_fork.c\
			run_command.c\
			exec_env.c\
			exec_exit.c\
			exec_setenv.c\
			exec_unsetenv.c\
			exec_echo.c\
			exec_cd.c\
			parse_prompt.c
SRCS_PATH = srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJ_NAME = $(SRCS_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAGS =	-Wall -Werror -Wextra
INC	= includes/

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(FLAGS) -I $(INC) -L ./libft/ -lft -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	gcc -c $(FLAGS) -I $(INC) -o $@ $<

clean:
	make -C libft/ clean
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
