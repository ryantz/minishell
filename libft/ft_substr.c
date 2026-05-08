/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:04:46 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:28:09 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	p_substr = malloc(sizeof(char) * len + 1);
	if (!p_substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p_substr[i] = s[start + i];
		i++;
	}
	p_substr[i] = '\0';
	return (p_substr);
}

//int	main(void)
//{
//	char	*sub;
//	char const *s = "hello there stranger";
//	unsigned int start = 6;
//	size_t len = 12;
//	sub = ft_substr(s, start, len);
//	printf("%s\n", sub);
//	free(sub);
//	return (0);
//}
