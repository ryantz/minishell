#include "minishell.h"

static t_status	count_argv(t_token *cursor, int *argc);
static t_status	is_redir_type(t_token_type type);
static t_status	add_redir(t_cmd *cmd, t_token **cursor);

t_status	parse_one_cmd(t_token **cursor, t_cmd **out)
{
	t_cmd	*cmd;
	int		argc;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (E_FALSE);
	cmd->redirs = NULL;
	cmd->next = NULL;
	if (count_argv(*cursor, &argc) == E_FALSE)
		return (free(cmd), E_FALSE);
	cmd->argv = malloc((argc + 1) * sizeof(char *));
	if (!cmd->argv)
		return (free(cmd), E_FALSE);
	i = 0;
	while (*cursor && (*cursor)->type != PIPE
		&& (*cursor)->type != AND && (*cursor)->type != OR)
	{
		if ((*cursor)->type == ERROR)
			return (free(cmd->argv), free(cmd), E_FALSE);
		if (is_redir_type((*cursor)->type) == E_TRUE)
		{
			if (add_redir(cmd, cursor) == E_FALSE)
				return (free(cmd->argv), free(cmd), E_FALSE);
		}
		else
		{
			cmd->argv[i++] = ft_strdup((*cursor)->value);
			*cursor = (*cursor)->next;
		}
	}
	cmd->argv[i] = NULL;
	*out = cmd;
	return (E_TRUE);
}

static t_status	count_argv(t_token *cursor, int *argc)
{
	*argc = 0;
	while (cursor && cursor->type != PIPE
		&& cursor->type != AND && cursor->type != OR)
	{
		if (is_redir_type(cursor->type) == E_TRUE)
		{
			cursor = cursor->next;
			if (!cursor)
				return (E_FALSE);
			cursor = cursor->next;
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

static t_status	is_redir_type(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_OUT_APPEND || type == READ_TO_DELIM)
		return (E_TRUE);
	return (E_FALSE);
}

static t_status	add_redir(t_cmd *cmd, t_token **cursor)
{
	t_redir	*redir;
	t_redir	*ptr;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (E_FALSE);
	if ((*cursor)->type == REDIR_IN)
		redir->type = R_IN;
	else if ((*cursor)->type == REDIR_OUT)
		redir->type = R_OUT;
	else if ((*cursor)->type == REDIR_OUT_APPEND)
		redir->type = R_APPEND;
	else
		redir->type = R_HEREDOC;
	*cursor = (*cursor)->next;
	if (!*cursor || (*cursor)->type != WORD)
		return (free(redir), E_FALSE);
	redir->target = ft_strdup((*cursor)->value);
	redir->next = NULL;
	*cursor = (*cursor)->next;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		ptr = cmd->redirs;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = redir;
	}
	return (E_TRUE);
}