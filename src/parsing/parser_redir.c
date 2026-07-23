/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:14:11 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/23 09:46:43 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status		skip_redir_pair(t_token **cursor);

t_status	is_redir_type(t_token_type type)
{
	if (type == R_IN || type == R_OUT || type == R_APPEND || type == R_HEREDOC)
		return (E_TRUE);
	return (E_FALSE);
}

t_status	add_redir(t_cmd *cmd, t_token **cursor)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (E_FALSE);
	redir->type = (*cursor)->type;
	redir->fd = -1;
	*cursor = (*cursor)->next;
	if (!*cursor || (*cursor)->type != WORD)
		return (free(redir), E_FALSE);
	redir->target = ft_strdup((*cursor)->value);
	if (!redir->target)
		return (free(redir), E_FALSE);
	redir->quoted = (*cursor)->quotes;
	redir->next = NULL;
	*cursor = (*cursor)->next;
	append_redir(cmd, redir);
	return (E_TRUE);
}

t_status	count_argv(t_token *cursor, int *argc)
{
	*argc = 0;
	while (cursor && cursor->type != PIPE
		&& cursor->type != L_AND && cursor->type != L_OR)
	{
		if (is_redir_type(cursor->type) == E_TRUE)
		{
			if (skip_redir_pair(&cursor) == E_FALSE)
				return (E_FALSE);
		}
		else
		{
			if (cursor->type == WORD)
				(*argc)++;
			cursor = cursor->next;
		}
	}
	return (E_TRUE);
}

static t_status	skip_redir_pair(t_token **cursor)
{
	*cursor = (*cursor)->next;
	if (!*cursor || (*cursor)->type != WORD)
		return (E_FALSE);
	*cursor = (*cursor)->next;
	return (E_TRUE);
}
