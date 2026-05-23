/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:17:48 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/24 00:19:18 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		determine_token_type(t_token **token, t_token **head,
					char *input, size_t *i);
static t_token	*find_last_token(t_token *head);
static void		append_token(t_token **head, t_token *token);

/*
 * @params: 
 * char *input -> input from stdin
 *
 * @return:
 * a pointer to the head of the token list created
 *
 * @brief:
 * creates a token list by appending all the tokens generated from
 * scanning through the while string
 */
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
