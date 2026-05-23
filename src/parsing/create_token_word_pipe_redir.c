/*
 * push into stack at every space
 * echo "hello">>text.txt
 */

#include "minishell.h"

t_token	*create_word_token(char *input, size_t *i)
{
	size_t	len;
	size_t	start;
	t_token	*token;
	char	*value;

	start = *i;
	len = 0;
	while (input[*i] && is_space(input[*i]) == E_FALSE
		&& is_operator(input[*i]) == E_FALSE)
	{
		len++;
		(*i)++;
	}
	value = ft_substr(input, start, len);
	token = create_token(value, WORD);
	if (input[start] == '\'')
		token->quotes = 1;
	else if (input[start] == '"')
		token->quotes = 2;
	free(value);
	return (token);
}

t_token	*create_pipe_token(char *input, size_t *i)
{
	t_token *token;

	(*i)++;
	if (input[*i] == '|')
	{
		(*i)++;
		token = create_token("||", OR);
	}
	else
		token = create_token("|", PIPE);
	return (token);
}

t_token	*create_redirect_delim_token(char *input, size_t *i)
{
	t_token *token;

	(*i)++;
	if (input[*i] == '<')
	{
		(*i)++;
		token = create_token("<<", READ_TO_DELIM);
	}
	else
		token = create_token("<", REDIR_IN);
	return (token);
}

t_token	*create_redirect_append_token(char *input, size_t *i)
{
	t_token *token;

	(*i)++;
	if (input[*i] == '>')
	{
		(*i)++;
		token = create_token(">>", REDIR_OUT_APPEND);
	}
	else
		token = create_token(">", REDIR_OUT);
	return (token);
}
