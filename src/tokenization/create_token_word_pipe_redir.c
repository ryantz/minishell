/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_word_pipe_redir.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:09:15 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 00:52:45 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @params: 
 * char *input -> input from stdin
 * size_t *i -> index that is passed by reference for updating
 *
 * @return:
 * a token that can be used to push into a token list in order
 *
 * @brief:
 * creates a token of type PIPE
 * with a value of |
 */
t_token	*create_pipe_token(char *input, size_t *i)
{
	t_token	*token;

	(*i)++;
	if (input[*i] == '|')
	{
		(*i)++;
		token = create_token("||", L_OR);
	}
	else
		token = create_token("|", PIPE);
	return (token);
}

/*
 * @params: 
 * char *input -> input from stdin
 * size_t *i -> index that is passed by reference for updating
 *
 * @return:
 * a token that can be used to push into a token list in order
 *
 * @brief:
 * creates a token of type REDIR_IN or READ_TO_DELIM
 * with value of << or < respectively
 */
t_token	*create_redirect_delim_token(char *input, size_t *i)
{
	t_token	*token;

	(*i)++;
	if (input[*i] == '<')
	{
		(*i)++;
		token = create_token("<<", R_HEREDOC);
	}
	else
		token = create_token("<", R_IN);
	return (token);
}

/*
 * @params: 
 * char *input -> input from stdin
 * size_t *i -> index that is passed by reference for updating
 *
 * @return:
 * a token that can be used to push into a token list in order
 *
 * @brief:
 * creates a token of type REDIR_OUT_APPEND or REDIR_OUT
 * with value of >> or > respectively
 */
t_token	*create_redirect_append_token(char *input, size_t *i)
{
	t_token	*token;

	(*i)++;
	if (input[*i] == '>')
	{
		(*i)++;
		token = create_token(">>", R_APPEND);
	}
	else
		token = create_token(">", R_OUT);
	return (token);
}
