# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbenazza <hbenazza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 17:57:32 by hbenazza          #+#    #+#              #
#    Updated: 2024/04/26 21:45:04 by hbenazza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = ./program/main.c ./program/reading_promp.c ./parse/parse.c ./libft/ft_atoi.c ./libft/ft_lstadd_back.c ./libft/ft_lstadd_front.c ./libft/ft_lstnew.c\
		./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strjoin.c ./libft/ft_strlen.c ./libft/ft_substr.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g

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
