#include "minishell.h"

int	main(int argc, char **argv)
{
	t_prompt	machine_info;
	char		*prompt;

	prompt = prompt_build(&machine_info);
	error_checks(argc, argv);
	if (prompt_loop(prompt))
		return (1);
	return (0);
}
