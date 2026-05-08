/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:38:01 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:28:59 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*cast;

	cast = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		*cast = '\0';
		cast++;
		i++;
	}
}

/*
int	main(void)
{
	char	s[12] = "hello there";
	char	*ptr = s + 6;
	printf("%s\n", s);
	ft_bzero(ptr, 5);
	printf("%s\n", s);
	printf("%c\n", s[8]); 
	printf("%c\n", s[9]); 
	printf("%c\n", s[10]); 
}
*/
