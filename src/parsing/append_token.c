#include "minishell.h"

static t_token	*find_last_token(t_token *token);

void	append_token(t_token **head, t_token *token)
{
	t_token	*last_element;

	if (head != NULL)
	{
		if (*head == NULL)
			*head = token;
		else
		{
			last_element = find_last_token(*head);
			last_element->next = token;
		}
	}
}

static t_token	*find_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}
