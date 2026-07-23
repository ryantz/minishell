/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:36:15 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 16:36:09 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char *nptr)
{
	int	offset;

	offset = 0;
	while (nptr[offset] == ' '
		|| (nptr[offset] >= 9 && nptr[offset] <= 13))
		offset++;
	return (offset);
}

long	ft_atol(const char *nptr)
{
	long	res;
	int		neg;
	int		i;

	i = ft_isspace(nptr);
	neg = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	if (neg)
		res *= -1;
	return (res);
}
