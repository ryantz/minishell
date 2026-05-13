#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*prompt;

// bitch
	if (argc < 2)
		return (1);
	prompt = readline(argv[1]);
	add_history(prompt);
	free(prompt);
	return (0);
}
