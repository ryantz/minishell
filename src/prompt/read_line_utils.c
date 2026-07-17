/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 00:00:00 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/17 00:00:00 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_newline(char *stash)
{
	int	i;

	if (!stash)
		return (-1);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*append_buf(char *stash, char *buf)
{
	if (!stash)
		return (ft_strdup(buf));
	return (ft_strjoin_free(stash, ft_strdup(buf)));
}

char	*extract_line(char *stash, int nl)
{
	if (nl < 0)
		return (ft_strdup(stash));
	return (ft_substr(stash, 0, nl));
}

char	*extract_remainder(char *stash, int nl)
{
	char	*rest;

	if (nl < 0)
	{
		free(stash);
		return (NULL);
	}
	rest = ft_substr(stash, nl + 1, ft_strlen(stash) - nl - 1);
	free(stash);
	return (rest);
}
