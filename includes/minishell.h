/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 23:45:42 by ryatan            #+#    #+#             */
/*   Updated: 2026/06/01 15:31:29 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# include "libft.h"

# define PATH_BUFFER 1024

typedef enum e_status
{
	E_TRUE,
	E_FALSE,
	E_SUCCESS,
	E_FAIL,
}	t_status;

typedef enum e_error
{
	WRONG_ARG_COUNT,
}	t_error;

typedef struct s_prompt
{
	char	*username;
	char	*hostname;
	char	*path;
	size_t	username_len;
	size_t	hostname_len;
	size_t	path_len;
	size_t	prompt_len;
}	t_prompt;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	READ_TO_DELIM,
	AND,
	OR,
	ERROR,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quotes;
	struct s_token	*next;
}	t_token;

//errors
void		print_error(t_error err_flag);
t_status	error_checks(int argc, char **argv);

//loggers
void		log_split(char **arr);
void		log_print(char *log_message, char *var);
void		log_list(t_token *token_list);

// frees	
void		free_all(char **arr);

//helpers
size_t		arr_len(char **arr);
t_status	is_space(char c);
t_status	is_lower(char c);
t_status	is_operator(char c);

//prompt	
int			prompt_loop(const char *prompt);
char		*prompt_build(t_prompt *machine_info);

//lexer
t_token		*create_token_list(char *input);

//create_token_and
t_token		*create_token(char *value, t_token_type type);
t_token		*create_and_token(char *input, size_t *i);

//create_token_word_pipe_redir
t_token		*create_word_token(char *input, size_t *i);
t_token		*create_pipe_token(char *input, size_t *i);
t_token		*create_redirect_delim_token(char *input, size_t *i);
t_token		*create_redirect_append_token(char *input, size_t *i);

//signal_handle
void	init_signals(void);
void	sigint_handler(int sig);
extern volatile sig_atomic_t g_signal;

#endif
