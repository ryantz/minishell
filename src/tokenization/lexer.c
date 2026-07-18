/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:17:48 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 22:08:04 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lex_next_token(char *input, size_t *i,
					t_lexer_params *lex_params);
static void		determine_token_type(t_token **head, char *input, size_t *i,
					t_lexer_params *lex_params);
static t_token	*find_last_token(t_token *head);
static void		append_token(t_token **head, t_token *token);

t_token	*create_token_list(char *input, t_env *env, int status)
{
	size_t			i;
	t_token			*head;
	t_lexer_params	lex_params;

	i = 0;
	head = NULL;
	lex_params.env = env;
	lex_params.status = status;
	determine_token_type(&head, input, &i, &lex_params);
	return (head);
}

static t_token	*lex_next_token(char *input, size_t *i,
			t_lexer_params *lex_params)
{
	if (input[*i] == '|')
		return (create_pipe_token(input, i));
	if (input[*i] == '&')
		return (create_and_token(input, i));
	if (input[*i] == '<')
		return (create_redirect_delim_token(input, i));
	if (input[*i] == '>')
		return (create_redirect_append_token(input, i));
	return (create_word_token(input, i, lex_params->env,
			lex_params->status));
}

static void	determine_token_type(t_token **head, char *input, size_t *i,
			t_lexer_params *lex_params)
{
	t_token	*token;

	while (input[*i])
	{
		if (is_space(input[*i]) == E_TRUE)
		{
			(*i)++;
			continue ;
		}
		token = lex_next_token(input, i, lex_params);
		if (token)
			append_token(head, token);
	}
}

static void	append_token(t_token **head, t_token *token)
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

static t_token	*find_last_token(t_token *head)
{
	t_token	*ptr_to_head;

	ptr_to_head = head;
	if (ptr_to_head == NULL)
		return (NULL);
	while (ptr_to_head->next != NULL)
		ptr_to_head = ptr_to_head->next;
	return (ptr_to_head);
}
