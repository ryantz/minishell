/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:52:13 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 20:15:43 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trim_seg(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p_trim;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0' || set[0] == '\0')
		return (ft_strdup(s1));
	while (s1[start] && ft_trim_seg(s1[start], set))
		start++;
	end = ft_strlen(s1);
	if (end > 0)
		end--;
	while (end > start && ft_trim_seg(s1[end], set))
		end--;
	p_trim = malloc(sizeof(char) * ((end - start + 1) + 1));
	if (!p_trim)
		return (NULL);
	i = 0;
	while (start <= end)
		p_trim[i++] = s1[start++];
	p_trim[i] = '\0';
	return (p_trim);
}

//int	main(void)
//{
//	char const *set = "$ .";
//	char const *s1 = " ...  $.... $  $";
//	char	*trimmed;
//	trimmed = ft_strtrim(s1, set);
//	printf("trimmed string:%s\n", trimmed);
//	free(trimmed);
//	return (0);
//}
