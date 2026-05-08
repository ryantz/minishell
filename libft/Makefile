# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 19:58:04 by ryatan            #+#    #+#              #
#    Updated: 2025/11/24 09:12:15 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# variables
NAME = libft.a
ARCHIVE = ar
ARCHIVE_FLAGS = rcs
COMPILER = cc
CFLAGS = -Wall -Werror -Wextra

SOURCE_FILES = ft_atoi.c  ft_bzero.c ft_calloc.c ft_isalnum.c \
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
				ft_memmove.c ft_memset.c ft_split.c ft_strchr.c \
				ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
				ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
				ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
				ft_tolower.c ft_toupper.c ft_putchar_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_putstr_fd.c 

SOURCE_FILES_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
					 ft_lstsize_bonus.c ft_lstlast_bonus.c \
					 ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
					 ft_lstclear_bonus.c ft_lstiter_bonus.c \
					 ft_lstmap_bonus.c

OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)
OBJECT_FILES_BONUS = $(SOURCE_FILES_BONUS:%.c=%.o)

# rules

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT_FILES)
	$(ARCHIVE) $(ARCHIVE_FLAGS) $(NAME) $(OBJECT_FILES)

all: $(NAME)

bonus : $(OBJECT_FILES_BONUS) $(OBJECT_FILES)
	$(ARCHIVE) $(ARCHIVE_FLAGS) $(NAME) $(OBJECT_FILES_BONUS)

clean:
	rm -rf $(OBJECT_FILES) $(OBJECT_FILES_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all bonus clean fclean re
