/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:06 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 08:30:29 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		update_pwd_variables(t_env **env, char *oldpwd);
static t_status	get_target(char **target, char **argv, t_env **env);

int	builtin_cd(char **argv, t_env **env)
{
	char	*target;
	char	*oldpwd;
	char	cwd_buffer[PATH_BUFFER];

	if (argv[1] && argv[2])
	{
		write_err("xiaoBij: cd: too many arguments");
		return (1);
	}
	if (get_target(&target, argv, env) == E_FALSE)
		return (1);
	oldpwd = getcwd(cwd_buffer, PATH_BUFFER);
	if (chdir(target) != 0)
	{
		write_err_arg("cd", target);
		return (1);
	}
	update_pwd_variables(env, oldpwd);
	return (0);
}

static void	update_pwd_variables(t_env **env, char *oldpwd)
{
	char	cwd_buffer[PATH_BUFFER];

	if (oldpwd)
	{
		env_set(env, "OLDPWD", ft_strdup(oldpwd));
		mark_as_export(env, "OLDPWD");
	}
	if (getcwd(cwd_buffer, PATH_BUFFER))
	{
		env_set(env, "PWD", ft_strdup(cwd_buffer));
		mark_as_export(env, "PWD");
	}
}

static t_status	get_target(char **target, char **argv, t_env **env)
{
	if (!argv[1])
	{
		*target = env_get(*env, "HOME");
		if (!*target)
		{
			write_err("cd: HOME not set");
			return (E_FALSE);
		}
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		*target = env_get(*env, "OLDPWD");
		if (!*target)
		{
			write_err("cd: OLDPWD not set");
			return (E_FALSE);
		}
		ft_putendl_fd(*target, 1);
	}
	else
		*target = argv[1];
	return (E_TRUE);
}
