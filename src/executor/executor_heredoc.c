/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 13:28:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/19 12:51:05 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*heredoc_next_line(void);
static t_status	heredoc_stop_check(char *line, t_redir *redir, int *stop);
static t_status	write_heredoc_line(char *line, t_heredoc_params *heredoc);
static t_status	fill_heredoc_pipe(t_heredoc_params *heredoc);

t_status	read_heredocs(t_redir *redirs, t_env *env, int exit_status)
{
	int					pipe_fd[2];
	t_heredoc_params	heredoc;

	while (redirs)
	{
		if (redirs->type == R_HEREDOC)
		{
			if (pipe(pipe_fd) == -1)
				return (E_FALSE);
			heredoc.write_fd = pipe_fd[1];
			heredoc.redir = redirs;
			heredoc.env = env;
			heredoc.exit_status = exit_status;
			if (fill_heredoc_pipe(&heredoc) == E_FALSE)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				return (E_FALSE);
			}
			close(pipe_fd[1]);
			redirs->fd = pipe_fd[0];
		}
		redirs = redirs->next;
	}
	return (E_TRUE);
}

static t_status	fill_heredoc_pipe(t_heredoc_params *heredoc)
{
	char	*line;
	int		stop;

	while (1)
	{
		line = heredoc_next_line();
		if (heredoc_stop_check(line, heredoc->redir, &stop) == E_FALSE)
			return (E_FALSE);
		if (stop)
			break ;
		if (write_heredoc_line(line, heredoc) == E_FALSE)
			return (E_FALSE);
	}
	return (E_TRUE);
}

static char	*heredoc_next_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	return (read_line_stdin());
}

static t_status	heredoc_stop_check(char *line, t_redir *redir, int *stop)
{
	if (g_sigint_flag)
	{
		g_sigint_flag = 0;
		free(line);
		return (E_FALSE);
	}
	if (!line)
	{
		write_err("warning: heredoc delimited by end-of-file");
		*stop = 1;
		return (E_TRUE);
	}
	if (ft_strcmp(line, redir->target) == 0)
	{
		free(line);
		*stop = 1;
		return (E_TRUE);
	}
	*stop = 0;
	return (E_TRUE);
}

static t_status	write_heredoc_line(char *line, t_heredoc_params *heredoc)
{
	char	*expanded;

	if (heredoc->redir->quoted)
		expanded = line;
	else
		expanded = expand_segment(ft_strdup(line), heredoc->env,
				heredoc->exit_status);
	if (!expanded)
		return (E_FALSE);
	write(heredoc->write_fd, expanded, ft_strlen(expanded));
	write(heredoc->write_fd, "\n", 1);
	free(expanded);
	return (E_TRUE);
}
