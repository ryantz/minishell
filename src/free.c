#include "minishell.h"

void	free_all(char **arr)
{
	size_t	len;

	len = arr_len(arr);
	while (len >= 0)
	{
		free(arr[len]);
		len--;
	}
	free(arr);
}
