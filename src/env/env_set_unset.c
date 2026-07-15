#include "minishell.h"

static t_status	env_set_append_new(t_env **env, char *key, char *value);

t_status	env_set(t_env **env, char *key, char *value)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
		{
			free(ptr->value);
			ptr->value = ft_strdup(value);
			ptr->has_value = 1;
			return (E_TRUE);
		}
		ptr = ptr->next;
	}
	return (env_set_append_new(env, key, value));
}

static t_status	env_set_append_new(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (E_FALSE);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (E_FALSE);
	}
	node->has_value = 1;
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

char	**env_to_array(t_env *env)
{
	char	**arr;
	t_env	*ptr;
	size_t	i;
	size_t	count;

	count = 0;
	ptr = env;
	while (ptr)
		count++, ptr = ptr->next;
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	ptr = env;
	while (ptr)
	{
		arr[i] = ft_strjoin_free(ft_strjoin(ptr->key, "="), ptr->value);
		ptr = ptr->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
