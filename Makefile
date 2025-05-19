# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoon <smoon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 15:05:46 by smoon             #+#    #+#              #
#    Updated: 2025/05/19 15:21:25 by smoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I./includes

NAME = philo

SRC_DIR = sources

OBJ_DIR = objects

SOURCES = sources/main.c \
			sources/errors.c \
			sources/ft_atoi.c \
			sources/ft_isdigit.c \
			sources/ft_putstr_fd.c \
			sources/initialisers.c \
			sources/uninitialisers.c

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(NAME)

objects/%.o: sources/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	chmod 777 $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) $(NAME)

re:	fclean all
