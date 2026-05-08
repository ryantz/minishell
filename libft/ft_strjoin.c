/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:37:41 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 11:00:36 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*p_strjoin;

	len = ft_strlen(s1) + ft_strlen(s2);
	p_strjoin = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	while (s1[j])
	{
		p_strjoin[i] = s1[j];
		j++;
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p_strjoin[i] = s2[j];
		j++;
		i++;
	}
	p_strjoin[i] = '\0';
	return (p_strjoin);
}

//int	main(void)
//{
//	char const *s1 = "hello ";
//	char const *s2 = "there";
//	char	*join;
//
//	join = ft_strjoin(s1, s2);
//	printf("%s\n", join);
//	free(join);
//	return (0);
//}
