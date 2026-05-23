/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 23:45:42 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/23 12:37:16 by ryatan           ###   ########.fr       */
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
	REDIRECT_IN,
	REDIRECT_OUT,
	AND,
	OR,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct	s_token	*next;
}	t_token;

//errors
void		print_error(t_error err_flag);
t_status	error_checks(int argc, char **argv);

//loggers
void		log_split(char **arr);
void		log_print(char *log_message, char *var);

// frees	
void		free_all(char **arr);

//helpers
size_t		arr_len(char **arr);

//prompt	
int			prompt_loop(const char *prompt);
char		*prompt_build(t_prompt *machine_info);

#endif
