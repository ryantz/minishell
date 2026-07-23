/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_outer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:13:57 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/16 00:50:42 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//splits tokens into pipelines on &&/||

static t_status	parse_one_pipeline(t_token **cursor, t_pipeline **out);
static t_status	build_pipeline_cmds(t_token **cursor, t_pipeline *pipeline);
static t_status	consume_link_operator(t_token **cursor, t_pipeline *pipeline);
//static t_status	consume_pipe_separator(t_token **cursor);

t_pipeline	*parse_tokens(t_token *tokens)
{
	t_pipeline	*head;
	t_pipeline	*pipeline;
	t_token		*cursor;

	head = NULL;
	cursor = tokens;
	while (cursor)
	{
		if (parse_one_pipeline(&cursor, &pipeline) == E_FALSE)
		{
			free_pipelines(head);
			return (NULL);
		}
		append_pipeline(&head, pipeline);
	}
	return (head);
}

static t_status	parse_one_pipeline(t_token **cursor, t_pipeline **out)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (E_FALSE);
	pipeline->cmds = NULL;
	pipeline->next = NULL;
	pipeline->link_to_next = NONE;
	if (build_pipeline_cmds(cursor, pipeline) == E_FALSE)
		return (free(pipeline), E_FALSE);
	if (consume_link_operator(cursor, pipeline) == E_FALSE)
	{
		free_cmd_list(pipeline->cmds);
		free(pipeline);
		return (E_FALSE);
	}
	*out = pipeline;
	return (E_TRUE);
}

static t_status	build_pipeline_cmds(t_token **cursor, t_pipeline *pipeline)
{
	t_cmd	*cmd;

	while (*cursor && (*cursor)->type != L_AND && (*cursor)->type != L_OR)
	{
		if (parse_one_cmd(cursor, &cmd) == E_FALSE)
		{
			free_cmd_list(pipeline->cmds);
			return (E_FALSE);
		}
		append_cmd(&pipeline->cmds, cmd);
		if (*cursor && (*cursor)->type == PIPE)
		{
			*cursor = (*cursor)->next;
			if (!*cursor || (*cursor)->type == PIPE
				|| (*cursor)->type == L_AND || (*cursor)->type == L_OR)
			{
				free_cmd_list(pipeline->cmds);
				return (E_FALSE);
			}
		}
	}
	if (!pipeline->cmds)
		return (E_FALSE);
	return (E_TRUE);
}

// static t_status	consume_pipe_separator(t_token **cursor)
// {
// 	if ((*cursor)->type != PIPE)
// 		return (E_TRUE);
// 	*cursor = (*cursor)->next;
// 	if (!*cursor)
// 		return (E_FALSE);
// 	return (E_TRUE);
// }

static t_status	consume_link_operator(t_token **cursor, t_pipeline *pipeline)
{
	if (!*cursor)
		return (E_TRUE);
	pipeline->link_to_next = NONE;
	if ((*cursor)->type == L_AND || (*cursor)->type == L_OR)
		pipeline->link_to_next = (*cursor)->type;
	*cursor = (*cursor)->next;
	if (!*cursor)
		return (E_FALSE);
	return (E_TRUE);
}
