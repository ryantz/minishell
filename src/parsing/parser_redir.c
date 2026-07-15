/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:14:11 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/08 16:35:16 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//redirection parsing + the argc-counting

static t_redir_type	get_redir_type(t_token_type type);
static t_status		skip_redir_pair(t_token **cursor);

t_status	is_redir_type(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_OUT_APPEND || type == READ_TO_DELIM)
		return (E_TRUE);
	return (E_FALSE);
}

t_status	add_redir(t_cmd *cmd, t_token **cursor)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (E_FALSE);
	redir->type = get_redir_type((*cursor)->type);
	*cursor = (*cursor)->next;
	if (!*cursor || (*cursor)->type != WORD)
		return (free(redir), E_FALSE);
	redir->target = ft_strdup((*cursor)->value);
	redir->next = NULL;
	*cursor = (*cursor)->next;
	append_redir(cmd, redir);
	return (E_TRUE);
}

// pass in the cursor and argc by reference (so it changes the argc value)
// argv of one cmd
// starting cannot be a | && ||
// cmd -> argv
// basically what comes after the cmd
t_status	count_argv(t_token *cursor, int *argc)
{
	*argc = 0;
	while (cursor && cursor->type != PIPE
		&& cursor->type != AND && cursor->type != OR)
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

// skip the redirect token to the next token
// after a redirect it should be a word. if not return false
static t_status	skip_redir_pair(t_token **cursor)
{
	*cursor = (*cursor)->next;
	if (!*cursor || (*cursor)->type != WORD)
		return (E_FALSE);
	*cursor = (*cursor)->next;
	return (E_TRUE);
}

static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == REDIR_IN)
		return (R_IN);
	if (type == REDIR_OUT)
		return (R_OUT);
	if (type == REDIR_OUT_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}
