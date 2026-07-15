#include "minishell.h"

int	builtin_echo(char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
