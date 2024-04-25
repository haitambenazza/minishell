# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 17:57:32 by hbenazza          #+#    #+#              #
#    Updated: 2024/04/25 13:50:33 by hbenazza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./program/main.c ./program/reading_promp.c ./parse/parse.c ./lib/ft_atoi.c ./lib/ft_lstadd_back.c ./lib/ft_lstadd_front.c ./lib/ft_lstnew.c\
		./lib/ft_split.c ./lib/ft_strdup.c ./lib/ft_strjoin.c ./lib/ft_strlen.c ./lib/ft_substr.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra

%.o: %.c
	cc $(CFLAGS) -c -o $@ $^

$(NAME): $(SRC) $(OBJ)
	@cc $(CFLAGS) -lreadline  $(OBJ) -o $(NAME)
	@echo "ready!"

clean:
	@rm -rf $(OBJ)
	@echo "objects removed!"

fclean:
	@rm -rf $(OBJ) $(NAME)
	@echo "objects and executable removed!"

re:fclean $(NAME)

all: $(NAME)
