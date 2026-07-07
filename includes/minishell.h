/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 23:45:42 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/07 19:56:25 by fkoh             ###   ########.fr       */
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

typedef enum e_redir_type
{
	R_IN, // < read from a file
	R_OUT, // > write to a file, truncating it
	R_APPEND, // >> write to a file, appending
	R_HEREDOC, // << read from stdin until a delimiter line
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv; //null terminated array of strings
	t_redir			*redirs; //linked list of t_redir
	struct s_cmd	*next;	//next command in the same pipe chain
}	t_cmd;

typedef enum e_link
{
	LINK_NONE,
	LINK_AND,
	LINK_OR,
}	t_link;

typedef struct s_pipeline
{
	t_cmd				*cmds; //linked list of t_cmd connected by |
	t_link				link_to_next; //operator after pipeline && or ||
	struct s_pipeline	*next; //pointer to next pipeline node
}	t_pipeline;

//errors
void		print_error(t_error err_flag);
t_status	error_checks(int argc, char **argv);

//loggers
void		log_split(char **arr);
void		log_print(char *log_message, char *var);
void		log_list(t_token *token_list);

// frees	
void		free_all(char **arr);
void		free_token_list(t_token *token_list);
void		free_pipelines(t_pipeline *pipelines);

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

//parser
t_pipeline *parse_tokens(t_token *tokens);

//signal_handle
void	init_signals(void);
void	sigint_handler(int sig);

#endif
