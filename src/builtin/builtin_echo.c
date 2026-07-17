/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:12 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/17 00:00:00 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_flag(char *s);
static void	set_flags(char *s, int *new_line, int *escape);
static void	print_escaped(char *str);

int	builtin_echo(char **argv)
{
	int	i;
	int	new_line;
	int	escape;

	i = 1;
	new_line = 1;
	escape = 0;
	while (argv[i] && is_echo_flag(argv[i]))
	{
		set_flags(argv[i], &new_line, &escape);
		i++;
	}
	while (argv[i])
	{
		if (escape)
			print_escaped(argv[i]);
		else
			ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

static int	is_echo_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || !s[1])
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n' && s[i] != 'e')
			return (0);
		i++;
	}
	return (1);
}

static void	set_flags(char *s, int *new_line, int *escape)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == 'n')
			*new_line = 0;
		else if (s[i] == 'e')
			*escape = 1;
		i++;
	}
}

static void	print_escaped(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i++;
			if (str[i] == 'n')
				ft_putstr_fd("\n", STDOUT_FILENO);
			else if (str[i] == 't')
				ft_putstr_fd("\t", STDOUT_FILENO);
			else if (str[i] == '\\')
				ft_putstr_fd("\\", STDOUT_FILENO);
			else if (str[i] == 'r')
				ft_putstr_fd("\r", STDOUT_FILENO);
			else
				write(STDOUT_FILENO, &str[i], 1);
			i++;
		}
		else
			write(STDOUT_FILENO, &str[i++], 1);
	}
}
