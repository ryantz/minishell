/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 02:33:58 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 21:15:20 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	env_set_append_new(t_env **env, char *key, char *value);
static t_status	is_valid_env_key(char *key);

t_status	env_set(t_env **env, char *key, char *value)
{
	t_env	*ptr;

	if (!env || is_valid_env_key(key) == E_FALSE)
	{
		free(value);
		return (E_FALSE);
	}
	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
		{
			free(ptr->value);
			ptr->value = value;
			ptr->has_value = (value != NULL);
			return (E_TRUE);
		}
		ptr = ptr->next;
	}
	return (env_set_append_new(env, key, value));
}

static t_status	is_valid_env_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (E_FALSE);
	i = 1;
	while (key[i])
	{
		if ((!ft_isalnum(key[i]) && key[i] != '_'))
			return (E_FALSE);
		i++;
	}
	return (E_TRUE);
}

static t_status	env_set_append_new(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (E_FALSE);
	node->key = ft_strdup(key);
	node->value = value;
	if (!node->key)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (E_FALSE);
	}
	node->has_value = (value != NULL);
	node->next = NULL;
	if (!*env)
		*env = node;
	else
		env_append(*env, node);
	return (E_TRUE);
}

t_status	env_unset(t_env **env, char *key)
{
	t_env	*ptr;
	t_env	*prev;

	if (!env || !*env || !key)
		return (E_FALSE);
	ptr = *env;
	prev = NULL;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
		{
			if (prev)
				prev->next = ptr->next;
			else
				*env = ptr->next;
			free(ptr->key);
			free(ptr->value);
			free(ptr);
			return (E_TRUE);
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return (E_FALSE);
}

t_status	env_touch(t_env **env, char *key)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
			return (E_TRUE);
		ptr = ptr->next;
	}
	return (env_set(env, key, NULL));
}
