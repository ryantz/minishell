/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isnumeric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:29:08 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 11:32:07 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	digits_overflow_long(char *digits, int is_neg)
{
	char	*max_pos;
	char	*max_neg;

	max_pos = "9223372036854775807";
	max_neg = "9223372036854775808";
	if (ft_strlen(digits) < 19)
		return (E_FALSE);
	if (ft_strlen(digits) > 19)
		return (E_TRUE);
	if (is_neg && ft_strncmp(digits, max_neg, 19) > 0)
		return (E_TRUE);
	if (!is_neg && ft_strncmp(digits, max_pos, 19) > 0)
		return (E_TRUE);
	return (E_FALSE);
}

t_status	is_numeric(char *str)
{
	size_t	i;
	int		is_neg;

	if (!str || !str[0])
		return (E_FALSE);
	i = 0;
	is_neg = (str[0] == '-');
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
	if (digits_overflow_long(str + (str[0] == '+' || str[0] == '-'),
			is_neg) == E_TRUE)
		return (E_FALSE);
	return (E_TRUE);
}
