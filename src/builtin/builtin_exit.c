#include "minishell.h"

int	builtin_exit(char **argv, int last_status)
{
	long	code;

	printf("exit\n");
	if (argv[1] && !is_numeric(argv[1]))
	{
		write_err("exit: numeric argument required");
		exit(2);
	}
	if (argv[1] && argv[2])
	{
		write_err("exit: too many arguments");
		return (1);
	}
	if (argv[1])
		code = ft_atol(argv[1]) % 256;
	else
		code = last_status;
	exit((int)code);
}
