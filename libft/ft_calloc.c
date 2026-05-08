/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 21:56:11 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 10:30:06 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ret;

	if (nmemb == 0 || size == 0)
	{
		ret = malloc(1);
		if (ret)
			ret[0] = '\0';
		return (ret);
	}
	if (size != 0 && nmemb > (size_t)(-1) / size)
		return (NULL);
	ret = malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, nmemb * size);
	return (ret);
}

//int main(void)
//{
//    // Use malloc (calloc) and ft_calloc for testing
//    char *test1 = calloc(3, sizeof(char));  // Standard calloc
//    char *test2 = ft_calloc(3, sizeof(char));  // Custom ft_calloc
//
//    // Check if allocation was successful
//    if (!test1 || !test2)
//    {
//        printf("Memory allocation failed!\n");
//        return 1;
//    }
//
//    // Print values allocated by calloc (test1) and ft_calloc (test2)
//    printf("Testing calloc (test1):\n");
//    for (size_t i = 0; i < 3; i++)
//    {
//        printf("test1[%zu]: %d\n", i, test1[i]);  // Should be 0
//    }
//
//    printf("Testing ft_calloc (test2):\n");
//    for (size_t i = 0; i < 3; i++)
//    {
//        printf("test2[%zu]: %d\n", i, test2[i]);  // Should be 0
//    }
//
//    // Free the allocated memory
//    free(test1);
//    free(test2);
//
//    return 0;
//}
