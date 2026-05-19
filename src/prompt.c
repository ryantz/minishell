#include "minishell.h"

int	prompt_loop(const char *prompt)
{
	char	*rl_return;
	char	**input_split;

	while (1)
	{
		rl_return = readline(prompt);
		log_print("String read from prompt:", rl_return);
		input_split = ft_split(rl_return, ' ');
		if (!input_split)
		{
			free_all(input_split);
			return (1);
		}
		log_split(input_split);
		if (!rl_return)
		{
			perror("Error-> readline() returns NULL");
			return (1);
		}
	}
	return (0);
}
