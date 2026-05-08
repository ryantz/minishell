/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:24:00 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 22:04:19 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	d_c;

	d_c = (unsigned char)c;
	while (*s)
	{
		if (*s == d_c)
			return ((char *)s);
		s++;
	}
	if (d_c == '\0')
		return ((char *)s);
	return (NULL);
}

//int	main(void)
//{
//	const char *s = "hello, there, hello";
//	int	c = ',';
//	printf("ft_strchr:%s\n", ft_strchr(s, c));
//	printf("strchr:%s\n", strchr(s, c));
//}
