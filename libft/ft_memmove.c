/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:24:02 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 22:48:07 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dest;
	const unsigned char	*c_src;

	c_dest = (unsigned char *)dest;
	c_src = (const unsigned char *)src;
	if (c_src < c_dest)
	{
		c_dest = c_dest + n - 1;
		c_src = c_src + n - 1;
		while (n > 0)
		{
			*c_dest-- = *c_src--;
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*c_dest++ = *c_src++;
			n--;
		}
	}
	return (dest);
}

//int	main(void)
//{
//	unsigned char	str1[100] = "unsigned char there";
//
//	ft_memmove(str1 + 9, str1, 4);
//	printf(" %s\n", str1);
//}
