/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:36:41 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/14 21:49:05 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (8);
	return (0);
}

/*
int	main(void)
{
	int	i;
	int	j;
	int	k;

	i = 'a';
	while (i <= 'z')
	{
		printf("ft_isalnum for %c : %d\n", i, ft_isalnum(i));
		printf("isalnum for %c : %d\n", i, isalnum(i));
		i++;
	}
	j = 'A';
	while (j <= 'Z')
	{
		printf("ft_isalnum for %c : %d\n", j, ft_isalnum(j));
		printf("isalnum for %c : %d\n", j, isalnum(j));
		j++;
	}
	k = '0';
	while (k <= '9')
	{
		printf("ft_isalnum for %c : %d\n", k, ft_isalnum(k));
		printf("isalnum for %c : %d\n", k, isalnum(k));
		k++;
	}
}
*/
