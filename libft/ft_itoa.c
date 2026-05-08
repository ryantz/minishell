/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:58:34 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:09:09 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len_of_int(int n)
{
	int	count;

	count = 0;
	if (n >= 0 && n <= 9)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_check_neg(long *ln)
{
	if (*ln < 0)
	{
		*ln *= -1;
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		int_len;
	int		i;
	char	*to_string;
	long	ln;

	ln = n;
	neg = ft_check_neg(&ln);
	int_len = ft_count_len_of_int(ln);
	to_string = malloc(sizeof(char) * int_len + 1 + neg);
	if (!to_string)
		return (NULL);
	i = int_len - 1 + neg;
	if (ln == 0)
		to_string[i] = 0 + '0';
	while (ln != 0)
	{
		to_string[i--] = (ln % 10) + '0';
		ln /= 10;
	}
	if (neg)
		to_string[0] = '-';
	to_string[int_len + neg] = '\0';
	return (to_string);
}

//int	main(void)
//{
//	int	n = -1001;
//	char	*string;
//	string = ft_itoa(n);
//	printf("%s\n", string);
//	free(string);
//	return (0);
//}
