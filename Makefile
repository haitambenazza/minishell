# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 17:57:32 by hbenazza          #+#    #+#              #
#    Updated: 2024/04/20 18:31:39 by hbenazza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./program/main.c ./program/reading_promp.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra -lreadline

%.o: %.c
	cc $(CFLAGS) -c -o $@ $^

$(NAME): $(SRC) $(OBJ)
	@cc $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "ready!"

clean:
	@rm -rf $(OBJ)
	@echo "objects removed!"

fclean:
	@rm -rf $(OBJ) $(NAME)
	@echo "objects and executable removed!"

re:fclean $(NAME)

all: $(NAME)
