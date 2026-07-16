#include "minishell.h"

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->has_value && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
