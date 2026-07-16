#include "minishell.h"

// argv[0] is cd
t_status	builtin_cd(char **argv, t_env **env)
{
	char	*target;
	char	*oldpwd;
	char	cwd_buffer[PATH_BUFFER];

	if (get_target(&target, argv, env) == E_FALSE)
		return (E_FALSE);
	oldpwd = getcwd(cwd_buffer, PATH_BUFFER);
	if (chdir(target) != 0)
	{
		write_err_arg("cd", target);
		return (E_FALSE);
	}
	if (oldpwd)
		env_set(env, "OLDPWD", ft_strdup(oldpwd));
	if (getcwd(cwd_buffer, PATH_BUFFER))
		env_set(env, "PWD", ft_strdup(cwd_buffer));
	return (E_TRUE);
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
		printf("%s\n", *target);
	}
	else
		*target = argv[1];
	return (E_TRUE);
}
