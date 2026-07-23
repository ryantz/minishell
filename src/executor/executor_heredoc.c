/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 13:28:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 10:01:31 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	process_one_heredoc(t_redir *head, t_redir *redir, t_env *env,
					int exit_status);
static void		close_heredoc_fds(t_redir *redirs, t_redir *stop_at);
static t_status	heredoc_stop_check(char *line, t_redir *redir, int *stop);
static t_status	fill_heredoc_pipe(t_heredoc_params *heredoc);

t_status	read_heredocs(t_redir *redirs, t_env *env, int exit_status)
{
	t_redir				*head;

	head = redirs;
	while (redirs)
	{
		if (redirs->type == R_HEREDOC)
		{
			if (process_one_heredoc(head, redirs, env, exit_status == E_FALSE))
				return (E_FALSE);
		}
		redirs = redirs->next;
	}
	return (E_TRUE);
}

static t_status	process_one_heredoc(t_redir *head, t_redir *redir, t_env *env,
			int exit_status)
{
	int					pipe_fd[2];
	t_heredoc_params	heredoc;

	if (pipe(pipe_fd) == -1)
		return (close_heredoc_fds(head, redir), E_FALSE);
	heredoc.write_fd = pipe_fd[1];
	heredoc.redir = redir;
	heredoc.env = env;
	heredoc.exit_status = exit_status;
	if (fill_heredoc_pipe(&heredoc) == E_FALSE)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (close_heredoc_fds(head, redir), E_FALSE);
	}
	close(pipe_fd[1]);
	redir->fd = pipe_fd[0];
	return (E_TRUE);
}

static void	close_heredoc_fds(t_redir *redirs, t_redir *stop_at)
{
	while (redirs && redirs != stop_at)
	{
		if (redirs->type == R_HEREDOC && redirs->fd != -1)
			close(redirs->fd);
		redirs = redirs->next;
	}
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

static t_status	heredoc_stop_check(char *line, t_redir *redir, int *stop)
{
	if (g_sigint_flag)
	{
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
