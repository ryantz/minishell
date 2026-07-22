/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:30 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 21:14:24 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv, t_env *env)
{
	char	*pwd;
	char	cwd[PATH_BUFFER];

	if (argv[1])
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	pwd = env_get(env, "PWD");
	if (pwd)
		return (ft_putendl_fd(pwd, STDOUT_FILENO), 0);
	if (!getcwd(cwd, PATH_BUFFER))
		return (1);
	return (ft_putendl_fd(cwd, STDOUT_FILENO), 0);
}
