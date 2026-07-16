/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:10 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 18:10:11 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_is_var_start(char *str, int i)
{
	if (str[i] != '$')
		return (0);
	if (str[i + 1] == '?')
		return (1);
	if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
		return (1);
	return (0);
}

int	expand_calc_len(char *str, t_env *env, int exit_status)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (expand_is_var_start(str, i))
		{
			value = expand_get_value(str, &i, env, exit_status);
			len += ft_strlen(value);
			free(value);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
