# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/08 23:35:05 by ryatan            #+#    #+#              #
#    Updated: 2026/07/23 10:13:06 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
COMPILER = cc
READLINE_PREFIX = $(shell brew --prefix readline 2>/dev/null)
INCLUDE = -Iincludes -Ilibft -I$(READLINE_PREFIX)/include
CFLAGS = -Wall -Wextra -Werror
EXT_LIBS = -L$(READLINE_PREFIX)/lib -lreadline
# # from readline_prefix to ext_libs is for Apple Silicon
# INCLUDE = -Iincludes -Ilibft
# CFLAGS = -Wall -Wextra -Werror
# EXT_LIBS = -lreadline

OBJ_DIR = build
SRC_DIR = src
HLP_DIR = helpers
TOKEN_DIR = tokenization
PAR_DIR = parsing
PRM_DIR = prompt
ENV_DIR = env
BUILTIN_DIR = builtin
EXPAND_DIR = expansion
EXE_DIR = executor

SRC =  $(SRC_DIR)/$(HLP_DIR)/errors.c \
	   $(SRC_DIR)/$(HLP_DIR)/free_pipeline.c \
	   $(SRC_DIR)/$(HLP_DIR)/free.c \
	   $(SRC_DIR)/$(HLP_DIR)/ft_strcmp.c \
	   $(SRC_DIR)/$(HLP_DIR)/ft_strjoin_free.c \
	   $(SRC_DIR)/$(HLP_DIR)/helpers.c \
	   $(SRC_DIR)/$(HLP_DIR)/loggers.c 

SRC += $(SRC_DIR)/$(PAR_DIR)/append_cmd.c \
	   $(SRC_DIR)/$(PAR_DIR)/append_pipeline.c \
	   $(SRC_DIR)/$(PAR_DIR)/append_redir.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_cmd.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_outer.c \
	   $(SRC_DIR)/$(PAR_DIR)/parser_redir.c \
	   
SRC += $(SRC_DIR)/$(TOKEN_DIR)/create_token_and.c \
	   $(SRC_DIR)/$(TOKEN_DIR)/create_token_word_pipe_redir.c \
	   $(SRC_DIR)/$(TOKEN_DIR)/create_token_word.c \
	   $(SRC_DIR)/$(TOKEN_DIR)/lexer.c

SRC += $(SRC_DIR)/$(PRM_DIR)/prompt_build.c \
	   $(SRC_DIR)/$(PRM_DIR)/prompt_loop.c \
	   $(SRC_DIR)/$(PRM_DIR)/signal_handle.c \
	   $(SRC_DIR)/$(PRM_DIR)/read_line.c \
	   $(SRC_DIR)/$(PRM_DIR)/read_line_utils.c \

SRC += $(SRC_DIR)/$(ENV_DIR)/env_get.c \
	   $(SRC_DIR)/$(ENV_DIR)/env_list.c \
	   $(SRC_DIR)/$(ENV_DIR)/env_set_unset.c \
	   $(SRC_DIR)/$(ENV_DIR)/env_to_array.c \
	   $(SRC_DIR)/$(ENV_DIR)/env_export.c \
	   $(SRC_DIR)/$(ENV_DIR)/print_sorted_env.c

SRC += $(SRC_DIR)/$(EXPAND_DIR)/expand_build.c \
	   $(SRC_DIR)/$(EXPAND_DIR)/expand_len.c \
	   $(SRC_DIR)/$(EXPAND_DIR)/expand_var.c

SRC += $(SRC_DIR)/$(EXE_DIR)/executor_exec.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_heredoc.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_heredoc_utils.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_pipeline.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_pipeline_fork.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_pipeline_wait.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_prepare_exec_struct.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_errors.c \
	   $(SRC_DIR)/$(EXE_DIR)/executor_redir.c

SRC += $(SRC_DIR)/$(BUILTIN_DIR)/builtin_cd.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_detection.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_echo.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_env.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_exit.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_export.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_pwd.c \
	   $(SRC_DIR)/$(BUILTIN_DIR)/builtin_unset.c

SRC += $(SRC_DIR)/main.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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
