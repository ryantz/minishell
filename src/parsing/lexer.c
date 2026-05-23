#include "minishell.h"

/* TODO: 
 * create a lexer to parse the arguments
 */

t_token	*create_token_list(char *input)
{
	size_t	i;
	t_token *token;
	t_token *head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		if (is_space(input[i]) == E_TRUE)
		{
			i++;
			continue;
		}
		else if (input[i] == '|')
			token = create_pipe_token(input, &i);
		else if (input[i] == '&')
			token = create_and_token(input, &i);
		else if (input[i] == '<')
			token = create_redirect_delim_token(input, &i);
		else if (input[i] == '>')
			token = create_redirect_append_token(input, &i);
		else
			token = create_word_token(input, &i);
		if (token)
			append_token(&head, token);
	}
	return (head);
}
