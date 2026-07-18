/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 13:28:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 13:41:17 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_next_line(void);
static t_status	fill_heredoc_pipe(int write_fd, t_redir *redir, t_env *env,
		int exit_status);

t_status	read_heredocs(t_redir *redirs, t_env *env, int exit_status)
{
	int	pipe_fd[2];

	while (redirs)
	{
		if (redirs->type == R_HEREDOC)
		{
			if (pipe(pipe_fd) == -1)
				return (E_FALSE);
			if (fill_heredoc_pipe(pipe_fd[1], redirs, env,
						exit_status) == E_FALSE)
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

static t_status	fill_heredoc_pipe(int write_fd, t_redir *redir, t_env *env,
		int exit_status)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = heredoc_next_line();
		if (g_sigint_flag)
		{
			g_sigint_flag = 0;
			free(line);
			return (E_FALSE);
		}
		if (!line)
		{
			write_err("warning: heredoc delimited by end-of-file");
			break;
		}
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break;
		}
		if (redir->quoted)
			expanded = line;
		else
			expanded = expand_segment(ft_strdup(line), env, exit_status);
		if (redir->quoted)
			free(line);
		if (!expanded)
			return (E_FALSE);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		if (!redir->quoted)
			free(expanded);
	}
	return (E_TRUE);
}

static char	*heredoc_next_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	return (read_line_stdin());
}
