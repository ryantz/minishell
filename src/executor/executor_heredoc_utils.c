/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 10:01:41 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 10:01:41 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_next_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	return (read_line_stdin());
}

t_status	write_heredoc_line(char *line, t_heredoc_params *heredoc)
{
	char	*expanded;

	if (heredoc->redir->quoted)
		expanded = line;
	else
		expanded = expand_segment(line, heredoc->env,
				heredoc->exit_status);
	if (!expanded)
		return (E_FALSE);
	write(heredoc->write_fd, expanded, ft_strlen(expanded));
	write(heredoc->write_fd, "\n", 1);
	free(expanded);
	return (E_TRUE);
}
