# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/01 23:59:56 by kaidda-s          #+#    #+#              #
#    Updated: 2026/02/03 19:11:36 by kaidda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -I include
RM			= rm -rf

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/utilis.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/philo.c \
			  $(SRC_DIR)/routine.c \
			  $(SRC_DIR)/actions.c \
			  $(SRC_DIR)/monitor.c \
			  $(SRC_DIR)/time.c

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅ philo compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@echo "🧹 Object files cleaned!"

fclean: clean
	$(RM) $(NAME)
	@echo "🧹 Executable cleaned!"

re: fclean all

.PHONY: all clean fclean re
