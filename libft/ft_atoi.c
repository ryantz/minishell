/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:36:15 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/18 12:22:10 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char *nptr)
{
	int	offset;

	offset = 0;
	while (nptr[offset] == ' '
		|| (nptr[offset] >= 9 && nptr[offset] <= 13))
		offset++;
	return (offset);
}

static int	ft_ten_power(int val, int times)
{
	int	i;

	i = 0;
	while (i < times)
	{
		val *= 10;
		i++;
	}
	return (val);
}

static int	ft_strlen_only_numbers(const char *nptr)
{
	int	len;

	len = 0;
	while (nptr[len] && (nptr[len] >= '0' && nptr[len] <= '9'))
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	long unsigned int	len;
	long unsigned int	offset;
	int					res;
	int					times;
	int					sign;

	res = 0;
	times = 0;
	sign = 0;
	offset = ft_isspace(nptr);
	if (nptr[offset] == '-' || nptr[offset] == '+')
		sign = 1;
	len = ft_strlen_only_numbers(nptr + offset + sign);
	while (len > 0)
	{
		res += ft_ten_power((nptr[offset + len - (!sign)] - '0'), times);
		times++;
		len--;
	}
	if (nptr[offset] == '-')
		res *= -1;
	return (res);
}

/*
int	main(void)
{
	const char *nptr = "         \t\n\v\f\r01234abc21";
	printf("%d\n", atoi(nptr));
	printf("%d\n", ft_atoi(nptr));
}
*/
