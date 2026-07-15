#include "minishell.h"

static int		is_valid_identifier(char *str);
static void		print_export_error(char *arg);
static void		export_one(t_env **env, char *arg);

int	builtin_export(t_env **env, char **args)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_export_error(args[i]);
			status = 1;
		}
		else
			export_one(env, args[i]);
		i++;
	}
	return (status);
}

static void	export_one(t_env **env, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		if (key)
			env_set(env, key, eq + 1);
		free(key);
	}
	else
		env_touch(env, arg);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}