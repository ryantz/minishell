/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:03 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/08 14:33:07 by fkoh             ###   ########.fr       */
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
t_status	is_numeric(char *str)
{
	size_t	i;

	if (!str || !str[0])
		return (E_FALSE);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (E_FALSE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (E_FALSE);
		i++;
	}
	return (E_TRUE);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}
