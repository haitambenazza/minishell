# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkoulal <tkoulal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 17:57:32 by hbenazza          #+#    #+#              #
#    Updated: 2024/05/30 14:04:11 by tkoulal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = ./program/main.c\
	./program/reading_promp.c \
	./parse/parse.c\
	./parse/lexer.c\
	./parse/tokens.c\
	./libft/ft_atoi.c\
	./libft/ft_lstadd_back.c \
	./libft/ft_lstadd_front.c \
	./libft/ft_lstsize.c \
	./libft/ft_lstnew.c	\
	./libft/ft_split.c \
	./libft/ft_strdup.c \
	./libft/ft_strjoin.c \
	./libft/ft_strlen.c \
	./libft/ft_substr.c \
	./libft/ft_strncmp.c\
	./libft/ft_strtrim.c\
	./libft/ft_strchr.c\
	./execution/execution.c\
	./execution/excute_cmd.c\
	./execution/check_built_in.c\
	./execution/clean_up.c\
	./built-in/commands1.c\
	./parse/init_struct.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g 

%.o: %.c
	cc $(CFLAGS) -c -o $@ $^

all: $(NAME)
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

.SECONDARY : OBJ
