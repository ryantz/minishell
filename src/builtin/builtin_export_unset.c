#include "minishell.h"

int	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*eq;
	char	*key;

	i = 1;
	if (!argv[1])
		return (print_sorted_env(*env), 0);
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			key = ft_substr(argv[i], 0, eq - argv[i]);
			env_set(env, key, eq + 1);
			free(key);
		}
		else
			env_set(env, argv[i], "");
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_unset(env, argv[i]);
		i++;
	}
	return (0);
}