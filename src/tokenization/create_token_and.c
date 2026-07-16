/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_and.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:50 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 18:10:53 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	token->quotes = 0;
	token->next = NULL;
	return (token);
}

t_token	*create_and_token(char *input, size_t *i)
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
