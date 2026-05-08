/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:00:55 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:30:17 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
int	main(void)
{
	int	i;

	i = 0;
	// 3 return 0s after 127
	while (i <= 130)
	{
		printf("ft_ascii val: %c, result: %d\n", i, ft_isascii(i));
		printf("ascii val: %c, result: %d\n", i, isascii(i));
		i++;
	}
}
*/
