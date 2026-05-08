/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:32:25 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 09:59:48 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	d_c;
	size_t			i;

	d_c = (unsigned char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == d_c)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == d_c)
		return ((char *)&s[i]);
	return (NULL);
}

//int	main(void)
//{
//	const char *s = "hello there";
//	int c = 'h';
//	printf("strrchr: %s\n", strrchr(s, c));
//	printf("ft_strrchr: %s\n", ft_strrchr(s, c));
//	return (0);
//}
