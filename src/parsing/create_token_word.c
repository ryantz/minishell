/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:15:11 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/08 16:20:00 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_quoted_segment(char *input, size_t *i, int *quote_type)
{
	char	quote;
	size_t	start;
	size_t	len;

	quote = input[*i];
	(*i)++;
	start = *i;
	len = 0;
	while (input[*i] && input[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (input[*i] == quote)
		(*i)++;
	if (quote == '\'')
		*quote_type = 1;
	else
		*quote_type = 2;
	return (ft_substr(input, start, len));
}

static char	*extract_bare_segment(char *input, size_t *i)
{
	size_t	start;
	size_t	len;

	start = *i;
	len = 0;
	while (input[*i] && input[*i] != '"' && input[*i] != '\''
		&& is_space(input[*i]) == E_FALSE
		&& is_operator(input[*i]) == E_FALSE)
	{
		len++;
		(*i)++;
	}
	return (ft_substr(input, start, len));
}

static t_token	*finalize_word_token(char *value, int any_quote)
{
	t_token	*token;

	if (*value == '\0' && !any_quote)
	{
		free(value);
		return (NULL);
	}
	token = create_token(value, WORD);
	token->quotes = any_quote;
	free(value);
	return (token);
}

t_token	*create_word_token(char *input, size_t *i)
{
	char	*value;
	char	*segment;
	int		seg_quote;
	int		any_quote;

	value = ft_strdup("");
	any_quote = 0;
	while (input[*i] && is_space(input[*i]) == E_FALSE
		&& is_operator(input[*i]) == E_FALSE)
	{
		if (input[*i] == '"' || input[*i] == '\'')
			segment = extract_quoted_segment(input, i, &seg_quote);
		else
		{
			segment = extract_bare_segment(input, i);
			seg_quote = 0;
		}
		if (seg_quote)
			any_quote = seg_quote;
		value = ft_strjoin_free(value, segment);
	}
	return (finalize_word_token(value, any_quote));
}
