/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_word_pipe_redir.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:09:15 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/23 23:32:23 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *input, size_t *i, size_t *start, size_t *len);

t_token	*create_word_token(char *input, size_t *i)
{
	size_t	len;
	size_t	start;
	t_token	*token;
	char	*value;
	int		quote_type;

	start = *i;
	len = 0;
	quote_type = check_quotes(input, i, &start, &len);
	if (quote_type == 0 && len == 0)
		return (NULL);
	value = ft_substr(input, start, len);
	token = create_token(value, WORD);
	token->quotes = quote_type;
	free(value);
	return (token);
}

static int	check_quotes(char *input, size_t *i, size_t *start, size_t *len)
{
	char	quotes;

	quotes = 0;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quotes = input[*i];
		(*i)++;
		*start = *i;
	}
	while (input[*i] && (quotes || (is_space(input[*i]) == E_FALSE
				&& is_operator(input[*i]) == E_FALSE)))
	{
		if (quotes && (input[*i] == quotes))
		{
			(*i)++;
			break ;
		}
		(*len)++;
		(*i)++;
	}
	if (quotes == '\'')
		return (1);
	if (quotes == '"')
		return (2);
	return (0);
}

t_token	*create_pipe_token(char *input, size_t *i)
{
	t_token	*token;

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
	t_token	*token;

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
	t_token	*token;

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
