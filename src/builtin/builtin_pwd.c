/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:30 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 18:09:31 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env *env)
{
	char	*pwd;
	char	cwd[PATH_BUFFER];

	pwd = env_get(env, "PWD");
	if (pwd)
		return (ft_putendl_fd(pwd, STDOUT_FILENO), 0);
	if (!getcwd(cwd, PATH_BUFFER))
		return (1);
	return (ft_putendl_fd(cwd, STDOUT_FILENO), 0);
}