#include "minishell.h"

int	main(int argc, char **argv)
{
	error_checks(argc, argv);
	if (prompt_loop("-t(-.-t)-> "))
		return (1);
	return (0);
}
