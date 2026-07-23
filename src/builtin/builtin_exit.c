/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:22 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 08:51:24 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("xiaoBij: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	builtin_exit(char **argv, int last_status, int *should_exit)
{
	long	code;

	if (argv[1] && argv[2])
	{
		write_err("xiaoBij: exit: too many arguments");
		return (1);
	}
	if (argv[1] && is_numeric(argv[1]) == E_FALSE)
	{
		print_numeric_error(argv[1]);
		*should_exit = 1;
		return (2);
	}
	if (argv[1])
		code = ft_atol(argv[1]) % 256;
	else
		code = last_status;
	*should_exit = 1;
	return ((int)code);
}
