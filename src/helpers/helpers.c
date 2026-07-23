/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:03 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 11:29:26 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

t_status	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (E_TRUE);
	return (E_FALSE);
}

t_status	is_lower(char c)
{
	if (c >= 97 && c <= 122)
		return (E_TRUE);
	return (E_FALSE);
}

t_status	is_operator(char c)
{
	char	*operators;
	int		i;

	operators = "|&><";
	i = 0;
	while (operators[i])
	{
		if (c == operators[i])
			return (E_TRUE);
		i++;
	}
	return (E_FALSE);
}
