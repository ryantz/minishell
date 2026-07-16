#include "minishell.h"

t_token	*create_redirect_append_token(char *input, size_t *i)
{
	t_token	*token;

	(*i)++;
	if (input[*i] == '&')
	{
		(*i)++;
		token = create_token("&&", L_AND);
	}
	else
		token = create_token("&", ERROR);
	return (token);
}
