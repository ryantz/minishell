/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 02:34:01 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 02:34:02 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_active_variables(t_env *env);

char	**env_to_array(t_env *env)
{
	char	**arr;
	t_env	*ptr;
	char	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (count_active_variables(env) + 1));
	if (!arr)
		return (NULL);
	ptr = env;
	i = 0;
	while (ptr)
	{
		if (ptr->exported && ptr->has_value && ptr->value != NULL)
		{
			tmp = ft_strjoin(ptr->key, "=");
			arr[i] = ft_strjoin_free(tmp, ft_strdup(ptr->value));
			if (!arr[i])
				return (free_all(arr), NULL);
			i++;
		}
		ptr = ptr->next;
	}
	arr[i] = NULL;
	return (arr);
}

static int	count_active_variables(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->exported && env->has_value && env->value != NULL)
			count++;
		env = env->next;
	}
	return (count);
}
