/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:28:33 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/14 22:34:36 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}

/*
int	main(void)
{
	int	i;

	i = 0;
	while (i <= 127)
	{
		printf("isprint ascii id %d, %c, return val: %d\n"
				, i, i, isprint(i));
		i++;
	}
	i = 0;
	while (i <= 127)
	{
		printf("ft_isprint ascii id %d, %c, return val: %d\n"
				, i, i, ft_isprint(i));
		i++;
	}
}
*/
