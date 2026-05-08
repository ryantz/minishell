/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 21:42:29 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 10:37:20 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (&dup[0]);
}

//int	main(void)
//{
//	char	*s1 = "hello there stranger";
//	char	*s2;
//	//s2 = strdup(s1);
//	s2 = ft_strdup(s1);
//	printf("%s\n", s2);
//	free(s2);
//	return (0);
//}
