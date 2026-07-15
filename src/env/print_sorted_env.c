#include "minishell.h"

static t_env	**env_to_ptr_array(t_env *env, size_t *count);
static void		sort_env_array(t_env **arr, size_t count);
static void		print_one_env(t_env *node);

void	print_sorted_env(t_env *env)
{
	t_env	**arr;
	size_t	count;
	size_t	i;

	arr = env_to_ptr_array(env, &count);
	if (!arr)
		return ;
	sort_env_array(arr, count);
	i = 0;
	while (i < count)
	{
		print_one_env(arr[i]);
		i++;
	}
	free(arr);
}

static t_env	**env_to_ptr_array(t_env *env, size_t *count)
{
	t_env	**arr;
	t_env	*ptr;
	size_t	i;

	*count = 0;
	ptr = env;
	while (ptr)
	{
		(*count)++;
		ptr = ptr->next;
	}
	arr = malloc((*count + 1) * sizeof(t_env *));
	if (!arr)
		return (NULL);
	i = 0;
	ptr = env;
	while (ptr)
	{
		arr[i++] = ptr;
		ptr = ptr->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env_array(t_env **arr, size_t count)
{
	size_t	i;
	size_t	j;
	t_env	*tmp;

	i = 1;
	while (i < count)
	{
		j = i;
		while (j > 0 && ft_strcmp(arr[j - 1]->key, arr[j]->key) > 0)
		{
			tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
			j--;
		}
		i++;
	}
}

static void	print_one_env(t_env *node)
{
	if (node->has_value)
		printf("declare -x %s=\"%s\"\n", node->key, node->value);
	else
		printf("declare -x %s\n", node->key);
}