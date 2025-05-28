# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoon <smoon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 15:05:46 by smoon             #+#    #+#              #
#    Updated: 2025/05/28 12:22:22 by smoon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

INCLUDES = -I./includes

NAME = philo

SRC_DIR = sources

OBJ_DIR = objects

SOURCES = sources/main.c \
			sources/eating.c \
			sources/eating2.c \
			sources/errors.c \
			sources/ft_atoi.c \
			sources/ft_isdigit.c \
			sources/ft_putstr_fd.c \
			sources/init.c \
			sources/init2.c \
			sources/monitoring.c \
			sources/printing.c \
			sources/simulation.c \
			sources/testing.c \
			sources/uninit.c \
			sources/utils.c

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(NAME)

objects/%.o: sources/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	chmod 777 $(NAME)

clean:
	rm -f $(OBJECTS)
	rm -f -d $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(NAME)

re:	fclean all
