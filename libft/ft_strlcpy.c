/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:16:22 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 10:09:12 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

//int	main(void)
//{
//	char	str1[12] = "hello there";
//	char	str2[12];
//
//	//printf("%zu\n", strlen(str1));
//	printf("%zu\n", ft_strlcpy(str2, str1, 0));
//	//strlcpy(str2, str1, 0);
//	//ft_strlcpy(str2, str1, 10);
//	//printf("%s\n", str2);
//	return (0);
//}
