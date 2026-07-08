#include "minishell.h"

int	builtin_cd(char **argv, t_env **env)
{
	char	old_cwd[PATH_BUFFER];
	char	new_cwd[PATH_BUFFER];
	char	*target;

	if (!getcwd(old_cwd, PATH_BUFFER))
		return (1);
	if (!argv[1])
		target = env_get(*env, "HOME");
	else
		target = argv[1];
	if (!target)
	{
		write_err("cd: HOME not set");
		return (1);
	}
	if (chdir(target) != 0)
	{
		write_err_arg("cd", target);
		return (1);
	}
	getcwd(new_cwd, PATH_BUFFER);
	env_set(env, "OLDPWD", old_cwd);
	env_set(env, "PWD", new_cwd);
	return (0);
}