/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:13:21 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 10:13:05 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size < dstlen)
		return (size + srclen);
	while (src[i] && (dstlen + i + 1 < size))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

//int	main(void)
//{
//	char first[] = "This is ";
//    char last[] = "a potentially long string";
//    int r;
//    int size = 100;
//    char buffer[size];
//
//    strcpy(buffer,first);
//    r = ft_strlcat(buffer,last, size);
//    puts(buffer);
//    printf("Value returned: %d\n",r);
//    if( r > size )
//        puts("String truncated");
//    else
//        puts("String was fully copied");
//
//    return(0);	
//}
