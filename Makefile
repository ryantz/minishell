# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/08 23:35:05 by ryatan            #+#    #+#              #
#    Updated: 2026/07/08 16:32:01 by fkoh             ###   ########.fr        #
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
PRM_DIR = prompt
ENV_DIR = env

SRC =  $(SRC_DIR)/$(HLP_DIR)/errors.c \
	   $(SRC_DIR)/$(HLP_DIR)/free_pipeline.c \
	   $(SRC_DIR)/$(HLP_DIR)/free.c \
	   $(SRC_DIR)/$(HLP_DIR)/helpers.c \
	   $(SRC_DIR)/$(HLP_DIR)/loggers.c \
	   $(SRC_DIR)/$(PAR_DIR)/append_cmd.c \
	   $(SRC_DIR)/$(PAR_DIR)/append_pipeline.c \
	   $(SRC_DIR)/$(PAR_DIR)/append_redir.c \
	   $(SRC_DIR)/$(PAR_DIR)/create_token_and.c \
	   $(SRC_DIR)/$(PAR_DIR)/create_token_word.c \
	   $(SRC_DIR)/$(PAR_DIR)/create_token_word_pipe_redir.c \
	   $(SRC_DIR)/$(PAR_DIR)/lexer.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_free.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_outer.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_redir.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_cmd.c \
	   $(SRC_DIR)/$(PRM_DIR)/prompt.c \
	   $(SRC_DIR)/$(PRM_DIR)/signal_handle.c \
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
