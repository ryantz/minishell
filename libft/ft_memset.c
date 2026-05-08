/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 13:49:59 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:31:02 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*c_s;
	size_t			i;

	c_s = (unsigned char *)s;
	i = 0;
	while (i++ < n)
	{
		*c_s++ = c;
	}
	return (s);
}

//int	main(void)
//{
//	//char	str[100] = "hello there";
//	int	strint[10] ;
//	ft_memset(strint, 1 , 10*sizeof(int));
//	int	i = 0;
//	while (i < 10)
//	{
//		printf("%d, ", strint[i]);
//		i++;
//	}
//	return (0);
//}
