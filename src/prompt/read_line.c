/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:00:00 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/18 21:57:20 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*finish_line(char **stash, int nl)
{
	char	*line;

	line = extract_line(*stash, nl);
	*stash = extract_remainder(*stash, nl);
	return (line);
}

char	*read_line_stdin(void)
{
	static char	*stash;
	char		buf[RL_CHUNK + 1];
	int			bytes;
	int			nl;

	nl = find_newline(stash);
	while (nl < 0)
	{
		bytes = read(STDIN_FILENO, buf, RL_CHUNK);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		stash = append_buf(stash, buf);
		nl = find_newline(stash);
	}
	if (!stash)
		return (NULL);
	return (finish_line(&stash, nl));
}
