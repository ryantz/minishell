/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:15:02 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/14 21:55:33 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
int	main(void)
{
	int	test_cap;
	int	test_noncap;
	int	res;
	
	test_cap = 'A';
	test_noncap = 'a';
	while (test_cap <= 'Z')
	{
		res = ft_tolower(test_cap);
		printf("%c\n", res);
		test_cap++;
	}
	while (test_noncap <= 'z')
	{
		res = ft_tolower(test_noncap);
		printf("%c\n", res);
		test_noncap++;
	} 
}
*/
