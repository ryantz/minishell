/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:22:24 by ryatan            #+#    #+#             */
/*   Updated: 2025/11/24 16:27:06 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;
	char	cn;

	ln = n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln *= -1;
	}
	if (ln >= 0 && ln <= 9)
	{
		cn = ln + '0';
		write(fd, &cn, 1);
	}
	else
	{
		ft_putnbr_fd(ln / 10, fd);
		ft_putnbr_fd(ln % 10, fd);
	}
}
