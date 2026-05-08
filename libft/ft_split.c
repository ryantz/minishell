/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:07:53 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/25 17:50:56 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char	const *s, char c)
{
	int	count;
	int	word_flag;
	int	i;

	count = 0;
	word_flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			word_flag = 0;
		else
		{
			if (word_flag == 0)
			{
				count++;
				word_flag = 1;
			}
		}
		i++;
	}
	return (count);
}

static char	*ft_allocate_inner(char const *s, char c, int *start, int *end)
{
	int		i;
	char	*inner_string;

	i = 0;
	while (s[*start] && s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] && s[*end] != c)
		(*end)++;
	inner_string = malloc(sizeof(char) * (*end - *start + 1));
	if (!inner_string)
		return (NULL);
	while (*start < *end)
		inner_string[i++] = s[(*start)++];
	inner_string[i] = '\0';
	return (inner_string);
}

static void	ft_free_all(int inner_len, char **arr)
{
	while (inner_len--)
		free(arr[inner_len]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		inner_len;
	int		i;
	int		start;
	int		end;

	start = 0;
	end = 0;
	inner_len = ft_count_words(s, c);
	arr = malloc(sizeof(char *) * (inner_len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < inner_len)
	{
		arr[i] = ft_allocate_inner(s, c, &start, &end);
		if (!arr[i])
			return (ft_free_all(inner_len - 1, arr), NULL);
		i++;
	}
	arr[inner_len] = NULL;
	return (arr);
}

//int	main(void)
//{
//	char	*s = "";
//	char	c = ',';
//	char	**arr;
//	int		i = 0;
//
//	arr = ft_split(s, c);
//	while (i < ft_count_words(s, c))
//	{
//		printf("%s\n", arr[i]);
//		i++;
//	}
//	ft_free_all(ft_count_words(s, c), arr);
//}
