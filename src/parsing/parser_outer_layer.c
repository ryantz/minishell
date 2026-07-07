#include "minishell.h"

//At the outer layer: Splits token list on AND/OR into pipelines
//1. Walk the token list, cut it into chunks (aka pipelines) wherever &&/|| appears 
//2. Wrap each chunk in a t_pipeline struct with a link_to_next tag saying how it connects to the one after it

static t_status	parse_one_pipeline(t_token **cursor, t_pipeline **out);
static void		append_pipeline(t_pipeline **head, t_pipeline *new);

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
	t_cmd		*cmd;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (E_FALSE);
	pipeline->cmds = NULL;
	pipeline->next = NULL;
	pipeline->link_to_next = LINK_NONE;
	while (*cursor && (*cursor)->type != AND && (*cursor)->type != OR)
	{
		if (parse_one_cmd(cursor, &cmd) == E_FALSE)
		{
			free(pipeline);
			return (E_FALSE);
		}
		append_cmd(&pipeline->cmds, cmd);
		if (*cursor && (*cursor)->type == PIPE)
			*cursor = (*cursor)->next;
	}
	if (*cursor)
	{
		if ((*cursor)->type == AND)
			pipeline->link_to_next = LINK_AND;
		else
			pipeline->link_to_next = LINK_OR;
		*cursor = (*cursor)->next;
	}
	*out = pipeline;
	return (E_TRUE);
}

static void	append_pipeline(t_pipeline **head, t_pipeline *new)
{
	t_pipeline	*ptr;

	if (!*head)
	{
		*head = new;
		return ;
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}