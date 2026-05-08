/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:18:57 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/14 21:28:41 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

/*
int	main(void)
{
	int	i, j;

	i = 'a';
	while (i <= 'z')
	{
		printf("ft_isalpha for %c : %d\n", i, ft_isalpha(i));
		printf("isalpha for %c : %d\n", i, isalpha(i));
		i++;
	}
	j = 'A';
	while (j <= 'Z')
	{
		printf("ft_isalpha for %c : %d\n", j, ft_isalpha(j));
		printf("isalpha for %c : %d\n", j, isalpha(j));
		j++;
	}	
}
*/
