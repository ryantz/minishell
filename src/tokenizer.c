/*
 * Tokenizer will read from readline in prompt_loop, prompt.c which is in the 
 * variable input_split. (char **)
 */
#include "minishell.h"

t_status	is_lower_char(char c);

t_status	create_token_stack(char **input_split)
{
	size_t	i;

	i = 0;
	while (i < arr_len(input_split))
	{
		i++;
	}
	return (E_SUCCESS);
}

int	create_token_node(char *value)
{
	return (0);
}


t_status	is_lower_char(char c)
{
	if (c >= 97 && c <= 122)
		return (E_TRUE);
	return (E_FALSE);
}
