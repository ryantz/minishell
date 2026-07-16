/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:05 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 18:10:06 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_expanded(char *str, char *out, t_env *env, int exit_status);

char	*expand_str(char *str, t_env *env, int exit_status)
{
	char	*out;
	int		len;

	len = expand_calc_len(str, env, exit_status);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	fill_expanded(str, out, env, exit_status);
	out[len] = '\0';
	return (out);
}

static void	fill_expanded(char *str, char *out, t_env *env, int exit_status)
{
	int		i;
	int		oi;
	int		j;
	char	*value;

	i = 0;
	oi = 0;
	while (str[i])
	{
		if (expand_is_var_start(str, i))
		{
			value = expand_get_value(str, &i, env, exit_status);
			j = 0;
			while (value[j])
				out[oi++] = value[j++];
			free(value);
		}
		else
			out[oi++] = str[i++];
	}
}

char	*expand_segment(char *segment, t_env *env, int status)
{
	char	*expanded;

	expanded = expand_str(segment, env, status);
	free(segment);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
}
