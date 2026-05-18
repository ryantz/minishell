#include "minishell.h"

int	main(int argc, char **argv)
{
	error_checks(argc);
	printf("%s", argv[0]);
}
