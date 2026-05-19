#include "minishell.h"

void	log_print(char *log_message, char *var)
{
	printf("%s %s\n", log_message, var);
}

void	log_split(char **arr)
{
	size_t	i;

	i = 0;
	printf("split view: [");
	while (i < arr_len(arr))
	{
		printf("[");
		printf("%s, ", arr[i]);
		printf("]");
		i++;
	}
	printf("]\n");
}
