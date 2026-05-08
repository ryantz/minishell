/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:40:30 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:30:34 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dp_s;

	dp_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (dp_s[i] == (unsigned char)c)
			return (&dp_s[i]);
		i++;
	}
	return (NULL);
}

//int	main(void)
//{
//	const char *s1 = "hello there stranger";
//	int	c = 'a';
//	size_t n = 16;
//	char	*s;
//	char	*s2;
//
//	s = memchr(s1, c, n);
//	s2 = ft_memchr(s1, c, n);
//	printf("memchr:%s\n", s);
//	printf("ft_memchr:%s\n", s2);
//}
