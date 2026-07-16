#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		i;

    i = 0;
	printf("argc: %d\n", argc);
	while (argv[i++])
		printf("argv i: %s\n", argv[i]);
	env = env_init(envp);
}
