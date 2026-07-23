/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 20:12:57 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 09:03:50 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	mark_as_export(t_env **env, char *key)
{
	t_env	*node;

	if (!env || !key)
		return (E_FALSE);
	node = *env;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			node->exported = 1;
			return (E_TRUE);
		}
		node = node->next;
	}
	return (E_FALSE);
}

void	set_shell_var(t_env **env, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return ;
	key = ft_substr(arg, 0, eq - arg);
	if (key)
		env_set(env, key, ft_strdup(eq + 1));
	free(key);
}
