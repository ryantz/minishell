/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:52:54 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 09:36:31 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dp_s1;
	const unsigned char	*dp_s2;
	size_t				i;

	dp_s1 = (const unsigned char *)s1;
	dp_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (dp_s1[i] != dp_s2[i])
			return (dp_s1[i] - dp_s2[i]);
		i++;
	}
	return (0);
}

//int	main(void)
//{
//	const char *s1 = "hello there stranger";
//	const char *s2 = "hello there str4nger";
//	size_t n = 16;
//	printf("ft_memcmp:%d\n", ft_memcmp(s1, s2, n));
//	printf("memcmp:%d\n", memcmp(s1, s2, n));
//	return (0);
//}
