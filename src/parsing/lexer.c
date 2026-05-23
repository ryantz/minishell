#include "minishell.h"

static void	determine_token_type(t_token **token, t_token **head, char *input,
				size_t *i);

t_token	*create_token_list(char *input)
{
	size_t	i;
	t_token	*token;
	t_token	*head;

	i = 0;
	head = NULL;
	token = NULL;
	determine_token_type(&head, &token, input, &i);
	return (head);
}

static void	determine_token_type(t_token **head, t_token **token, char *input,
				size_t *i)
{
	while (input[*i])
	{
		if (is_space(input[*i]) == E_TRUE)
		{
			(*i)++;
			continue ;
		}
		else if (input[*i] == '|')
			*token = create_pipe_token(input, i);
		else if (input[*i] == '&')
			*token = create_and_token(input, i);
		else if (input[*i] == '<')
			*token = create_redirect_delim_token(input, i);
		else if (input[*i] == '>')
			*token = create_redirect_append_token(input, i);
		else
			*token = create_word_token(input, i);
		if (*token)
			append_token(head, *token);
	}
}
