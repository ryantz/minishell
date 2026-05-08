/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:04:27 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/14 21:46:03 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

/*
#include <ctype.h>
int	main(void)
{
	printf("%d\n", isdigit('3'));
	printf("%d\n", isdigit('c'));
	printf("%d\n", ft_isdigit('4'));
	printf("%d\n", ft_isdigit('c'));
}
*/
