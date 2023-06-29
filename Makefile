# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 09:01:07 by jchamak           #+#    #+#              #
#    Updated: 2023/06/29 12:04:21 by jchamak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

SRC = main.c
SRCC = main_bonus.c

OBJ = $(SRC:.c=.o)
OBJJ = $(SRCC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	
$(OBJJ):
	$(CC) $(CFLAGS) -c $(SRCC)

$(LIBFT):
	make -C libft

bonus:
	make $(OBJJ)

clean:
	rm -rf $(OBJ) $(OBJJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
