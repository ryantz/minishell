# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/08 23:35:05 by ryatan            #+#    #+#              #
#    Updated: 2026/05/23 18:28:49 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
COMPILER = cc
INCLUDE = -Iincludes -Ilibft
CFLAGS = -Wall -Wextra -Werror
EXT_LIBS = -lreadline

OBJ_DIR = build
SRC_DIR = src
HLP_DIR = helpers
PAR_DIR = parsing

SRC =  $(SRC_DIR)/$(HLP_DIR)/errors.c \
	   $(SRC_DIR)/$(HLP_DIR)/free.c \
	   $(SRC_DIR)/$(HLP_DIR)/helpers.c \
	   $(SRC_DIR)/$(HLP_DIR)/loggers.c \
	   $(SRC_DIR)/$(PAR_DIR)/append_token.c \
	   $(SRC_DIR)/$(PAR_DIR)/create_token_and.c \
	   $(SRC_DIR)/$(PAR_DIR)/create_token_word_pipe_redir.c \
	   $(SRC_DIR)/$(PAR_DIR)/lexer.c \
	   $(SRC_DIR)/prompt.c \
	   $(SRC_DIR)/main.c

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(OBJ) $(LIBFT)
	$(COMPILER) $(CFLAGS) $(OBJ) $(LIBFT) $(EXT_LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
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
