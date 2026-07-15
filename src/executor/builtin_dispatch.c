#include "minishell.h"

typedef struct s_builtin
{
	char	*name;
	int		(*fn)(t_env **env, char **argv);
}	t_builtin;

static int	builtin_count(void);

t_status	is_builtin(char *name)
{
	static char	*names[] = {"cd", "export", "unset", "exit", "env", NULL};
	int			i;

	if (!name)
		return (E_FALSE);
	i = 0;
	while (names[i])
	{
		if (ft_strcmp(name, names[i]) == 0)
			return (E_TRUE);
		i++;
	}
	return (E_FALSE);
}

int	run_builtin_parent(t_cmd *cmd, t_env **env)
{
	static t_builtin	table[] = {
		{"cd", builtin_cd}, {"export", builtin_export},
		{"unset", builtin_unset}, {"exit", builtin_exit},
		{"env", builtin_env}
	};
	int	i;

	i = 0;
	while (i < builtin_count())
	{
		if (ft_strcmp(cmd->argv[0], table[i].name) == 0)
			return (table[i].fn(env, cmd->argv));
		i++;
	}
	return (1);
}

static int	builtin_count(void)
{
	return (5);
}
