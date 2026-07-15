#include "minishell.h"

t_status	env_touch(t_env **env, char *key)
{
	t_env	*node;

	if (env_get(*env, key))
		return (E_TRUE);
	node = malloc(sizeof(t_env));
	if (!node)
		return (E_FALSE);
	node->key = ft_strdup(key);
	node->value = ft_strdup("");
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (E_FALSE);
	}
	node->has_value = 0;
	node->next = NULL;
	if (!*env)
		*env = node;
	else
		env_append(*env, node);
	return (E_TRUE);
}