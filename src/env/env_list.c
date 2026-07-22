/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 02:33:55 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 02:35:52 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_node(char *key, char *value, int has_value, int exported);
void			env_append(t_env *head, t_env *node);

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*node;
	char	*equals_ptr;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equals_ptr = ft_strchr(envp[i], '=');
		if (equals_ptr)
			node = new_env_node(ft_substr(envp[i], 0, equals_ptr - envp[i]),
					ft_strdup(equals_ptr + 1), 1, 1);
		else
			node = new_env_node(ft_strdup(envp[i]), NULL, 0, 1);
		if (!node)
			return (free_env(head), NULL);
		if (!head)
			head = node;
		else
			env_append(head, node);
		i++;
	}
	return (head);
}

static t_env	*new_env_node(char *key, char *value, int has_value, int exported)
{
	t_env	*node;

	if (!key)
	{
		free(key);
		free(value);
		return (NULL);
	}
	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	node->key = key;
	node->value = value;
	node->has_value = has_value;
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	env_append(t_env *head, t_env *node)
{
	t_env	*ptr;

	if (!head || !node)
		return ;
	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = node;
}
