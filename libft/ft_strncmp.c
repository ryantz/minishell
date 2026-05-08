/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:19:14 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 17:22:44 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char *s1 = "hello there";
// 	const char *s2 = "helli";
// 	printf("%d\n", strncmp(s1, s2, 5));
// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	return (0);
// }
