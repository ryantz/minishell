/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:14:30 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/16 00:51:17 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//one command's argv, orchestrates redir calls

static t_status	build_cmd_argv(t_token **cursor, t_cmd *cmd, int *i);
static t_status	process_cmd_token(t_token **cursor, t_cmd *cmd, int *i);
static t_status	validate_cmd_content(t_cmd *cmd, int argc);
static void		free_partial_argv(char **argv, int built);

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
	if (build_cmd_argv(cursor, cmd, &i) == E_FALSE)
		return (E_FALSE);
	cmd->argv[i] = NULL;
	if (validate_cmd_content(cmd, i) == E_FALSE)
		return (free(cmd->argv), free(cmd), E_FALSE);
	*out = cmd;
	return (E_TRUE);
}

static t_status	build_cmd_argv(t_token **cursor, t_cmd *cmd, int *i)
{
	while (*cursor && (*cursor)->type != PIPE
		&& (*cursor)->type != L_AND && (*cursor)->type != L_OR)
	{
		if (process_cmd_token(cursor, cmd, i) == E_FALSE)
		{
			free_partial_argv(cmd->argv, *i);
			free_redirs_local(cmd->redirs);
			free(cmd);
			return (E_FALSE);
		}
	}
	return (E_TRUE);
}

static t_status	process_cmd_token(t_token **cursor, t_cmd *cmd, int *i)
{
	if ((*cursor)->type == ERROR)
		return (E_FALSE);
	if (is_redir_type((*cursor)->type) == E_TRUE)
		return (add_redir(cmd, cursor));
	cmd->argv[(*i)++] = ft_strdup((*cursor)->value);
	*cursor = (*cursor)->next;
	return (E_TRUE);
}

static t_status	validate_cmd_content(t_cmd *cmd, int argc)
{
	if (argc == 0 && !cmd->redirs)
		return (E_FALSE);
	return (E_TRUE);
}

static void	free_partial_argv(char **argv, int built)
{
	int	i;

	i = 0;
	while (i < built)
		free(argv[i++]);
	free(argv);
}
