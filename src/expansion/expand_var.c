/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:15 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 18:10:16 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *str, int *i);

char	*expand_get_value(char *str, int *i, t_env *env, int exit_status)
{
	char	*name;
	char	*value;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(exit_status));
	}
	name = get_var_name(str, i);
	if (!name)
		return (ft_strdup(""));
	value = env_get(env, name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*get_var_name(char *str, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	return (ft_substr(str, start, *i - start));
}
