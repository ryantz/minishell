#include "minishell.h"

void	free_all(char **arr)
{
	size_t	i;

	i = 0;
	while (i < arr_len(arr))
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
