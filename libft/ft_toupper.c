/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:16:48 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/14 21:58:04 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
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
		res = ft_toupper(test_cap);
		printf("%c\n", res);
		test_cap++;
	}
	while (test_noncap <= 'z')
	{
		res = ft_toupper(test_noncap);
		printf("%c\n", res);
		test_noncap++;
	} 
}
*/
