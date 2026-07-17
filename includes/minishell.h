/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 23:45:42 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 17:40:53 by ryatan           ###   ########.fr       */
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
# include <errno.h>
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
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC,
	L_AND,
	L_OR,
	ERROR,
	NONE,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quotes;
	struct s_token	*next;
}	t_token;

// parser: redirections
typedef struct s_redir
{
	t_token_type	type;
	char			*target; //string that comes after redir operator
	struct s_redir	*next; //next redir in one command
}	t_redir;

// parser: commands (one command, pipe-chained via ->next)
typedef struct s_cmd
{
	char			**argv; //null terminated array of strings
	t_redir			*redirs; //linked list of t_redir
	struct s_cmd	*next;	//next command in the same pipe chain
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd				*cmds; //linked list of t_cmd connected by |
	t_token_type		link_to_next; //operator after pipeline && or ||
	struct s_pipeline	*next; //pointer to next pipeline node
}	t_pipeline;

// environment (mutable list of KEY=VALUE, seeded from envp)
typedef struct s_env
{
	char			*key;
	char			*value;
	int				has_value;
	struct s_env	*next;
}	t_env;

//errors
void		print_error(t_error err_flag);
t_status	error_checks(int argc, char **argv);
void		write_err(char *err_msg);
void		write_err_arg(char *cmd, char *arg);

//loggers
void		log_split(char **arr);
void		log_print(char *log_message, char *var);
void		log_list(t_token *token_list);

// frees
void		free_all(char **arr);
void		free_token_list(t_token *token_list);
void		free_pipelines(t_pipeline *pipelines);
void		free_env(t_env *env);

//helpers
size_t		arr_len(char **arr);
t_status	is_space(char c);
t_status	is_lower(char c);
t_status	is_operator(char c);
t_status	is_numeric(char *str);
char		*ft_strjoin_free(char *s1, char *s2);
int 		ft_strcmp(const char *s1, const char *s2);

//prompt	
//int			prompt_loop(const char *prompt);
int			prompt_loop(const char *prompt, t_env **env);

char		*prompt_build(t_prompt *machine_info);
char		*read_line_stdin(void);
int			find_newline(char *stash);
char		*append_buf(char *stash, char *buf);
char		*extract_line(char *stash, int nl);
char		*extract_remainder(char *stash, int nl);

//lexer
t_token		*create_token_list(char *input, t_env *env, int status);

//create_token_and
t_token		*create_token(char *value, t_token_type type);
t_token		*create_and_token(char *input, size_t *i);

//create_token_word_pipe_redir
//t_token		*create_word_token(char *input, size_t *i);
t_token		*create_word_token(char *input, size_t *i, t_env *env, int status);
t_token		*create_pipe_token(char *input, size_t *i);
t_token		*create_redirect_delim_token(char *input, size_t *i);
t_token		*create_redirect_append_token(char *input, size_t *i);

char	*expand_segment(char *segment, t_env *env, int status);


//parser (outer layer: pipelines split on AND/OR)
t_pipeline	*parse_tokens(t_token *tokens);
void		append_cmd(t_cmd **head, t_cmd *new);
void		append_pipeline(t_pipeline **head, t_pipeline *new);

//parser: cmd building
t_status	parse_one_cmd(t_token **cursor, t_cmd **out);

//parser: redirections
void		append_redir(t_cmd *cmd, t_redir *redir);
t_status	is_redir_type(t_token_type type);
t_status	add_redir(t_cmd *cmd, t_token **cursor);
t_status	count_argv(t_token *cursor, int *argc);

//parser: cleanup
void		free_cmd_list(t_cmd *cmds);
void		free_redirs_local(t_redir *redirs);

//path resolution
char		*find_in_path(char *cmd, char **envp);
char		*get_env_value(char *key, char **envp);

//env
t_env		*env_init(char **envp);
void		env_append(t_env *head, t_env *node);
char		*env_get(t_env *env, char *key);
t_status	env_set(t_env **env, char *key, char *value);
t_status	env_unset(t_env **env, char *key);
t_status	env_touch(t_env **env, char *key);
char		**env_to_array(t_env *env);
void		free_env(t_env *env);

//builtins
t_status	is_builtin(char *cmd_name);
int			exec_builtin(t_cmd *cmd, t_env **env, int last_status);
int	builtin_cd(char **argv, t_env **env);
int			builtin_echo(char **argv);
int			builtin_pwd(void);
int			builtin_export(char **argv, t_env **env);
int			builtin_unset(char **argv, t_env **env);
int			builtin_env(t_env *env);
int			builtin_exit(char **argv, int last_status);
void		print_sorted_env(t_env *env);

//signal_handle
void		init_signals(void);
void		sigint_handler(int sig);

int	run_pipeline(t_pipeline *pipeline, t_env *env);

int	expand_calc_len(char *str, t_env *env, int exit_status);
int	expand_is_var_start(char *str, int i);
char	*expand_get_value(char *str, int *i, t_env *env, int exit_status);

t_status	apply_redirs(t_redir *redirs);
void	child_exec(t_cmd *cmd, int prev_fd, int *pipe_fd, t_env *env);

#endif
