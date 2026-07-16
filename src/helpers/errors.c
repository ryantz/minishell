/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:17:53 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 15:37:51 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_err(char *err_msg);
void	print_error(t_error err_flag);

t_status	error_checks(int argc, char **argv)
{
	if (argc > 1 || argv[1])
		return (print_error(WRONG_ARG_COUNT), E_FALSE);
	return (E_TRUE);
}

void	print_error(t_error err_flag)
{
	if (err_flag == WRONG_ARG_COUNT)
		write_err("Wrong argument count. Just run the executable ./minishell");
}

void	write_err_arg(char *cmd, char *arg)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, strerr(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	write_err(char *err_msg)
{
	int	len;

	len = ft_strlen(err_msg);
	write(2, err_msg, len);
	write(2, "\n", 1);
}
