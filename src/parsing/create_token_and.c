/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_and.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:17:44 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/08 16:10:07 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @params: 
 * char *value -> the value of the string that relates to the token
 * t_token_type type ->  the type of token
 *
 * @return:
 * a token for lexing
 *
 * @brief:
 * creates a token that contains the value, token type, quote type
 * and pointer to the next token if any
*/
t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		return (free(token), NULL);
	token->type = type;
	token->quotes = 0;
	token->next = NULL;
	return (token);
}

/*
 * @params: 
 * char *input -> input from stdin
 * size_t *i -> the index passed by reference
 *
 * @return:
 * a token that can be used to push into a token list in order
 *
 * @brief:
 * creates a token of type AND or ERROR
 * with a value of && or & respectively
*/
t_token	*create_and_token(char *input, size_t *i)
{
	t_token	*token;

	(*i)++;
	if (input[*i] == '&')
	{
		(*i)++;
		token = create_token("&&", AND);
	}
	else
		token = create_token("&", ERROR);
	return (token);
}
