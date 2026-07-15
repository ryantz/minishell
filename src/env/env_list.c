#include "minishell.h"

static t_env	*new_env_node(char *key, char *value, int has_value);
void	env_append(t_env *head, t_env *node);

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*node;
	char	*eq;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
			node = new_env_node(ft_substr(envp[i], 0, eq - envp[i]),
					ft_strdup(eq + 1), 1);
		else
			node = new_env_node(ft_strdup(envp[i]), ft_strdup(""), 0);
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

static t_env	*new_env_node(char *key, char *value, int has_value)
{
	t_env	*node;

	if (!key || !value)
		return (free(key), free(value), NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (free(key), free(value), NULL);
	node->key = key;
	node->value = value;
	node->has_value = has_value;
	node->next = NULL;
	return (node);
}

void	env_append(t_env *head, t_env *node)
{
	t_env	*ptr;

	ptr = head;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = node;
}

char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
