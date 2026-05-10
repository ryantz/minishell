# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/08 23:35:05 by ryatan            #+#    #+#              #
#    Updated: 2026/05/10 13:49:19 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
COMPILER = cc
INCLUDE = -Iinclude -Ilibft
CFLAGS = -Wall -Wextra -Werror
EXT_LIBS = -lreadline

OBJ_DIR = obj
SRC_DIR = src

SRC =  main.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(OBJ) $(LIBFT)
	$(COMPILER) $(CFLAGS) $(OBJ) $(LIBFT) $(EXT_LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
