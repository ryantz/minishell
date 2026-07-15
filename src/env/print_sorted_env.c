/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 02:34:05 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 02:39:35 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_nodes(t_env *env);
static void	sort_env_array(t_env **env, int size);
static void	display_sorted_env(t_env **arr, int size);

void	print_sorted_env(t_env *env)
{
	t_env	**sorted;
	t_env	*tmp;
	int		size;
	int		i;

	size = count_env_nodes(env);
	if (size == 0)
		return ;
	sorted = malloc(sizeof(t_env *) * size);
	if (!sorted)
		return ;
	i = 0;
	tmp = env;
	while (tmp)
	{
		sorted[i++] = tmp;
		tmp = tmp->next;
	}
	sort_env_array(sorted, size);
	display_sorted_env(sorted, size);
	free(sorted);
}

static void	sort_env_array(t_env **arr, int size)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j]->key, arr[j + 1]->key) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	display_sorted_env(t_env **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (arr[i]->value == NULL)
			printf("declare -x %s\n", arr[i]->key);
		else
			printf("declare -x %s=\"%s\"\n", arr[i]->key, arr[i]->value);
	}
}

static int	count_env_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
