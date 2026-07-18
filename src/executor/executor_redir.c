/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:00 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 13:27:43 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_fd(t_redir *redir);

t_status	apply_redirs(t_redir *redirs)
{
	int	fd;

	while (redirs)
	{
		fd = open_redir_fd(redirs);
		if (fd == -1)
			return (E_FALSE);
		if (redirs->type == R_IN || redirs->type == R_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirs = redirs->next;
	}
	return (E_TRUE);
}

static int	open_redir_fd(t_redir *redir)
{
	if (redir->type == R_IN)
		return (open(redir->target, O_RDONLY));
	if (redir->type == R_OUT)
		return (open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == R_APPEND)
		return (open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == R_HEREDOC)
		return (redir->fd);
	return (-1);
}
