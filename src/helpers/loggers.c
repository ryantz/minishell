#include "minishell.h"

static char	*get_token_type(t_token_type type);

void	log_print(char *log_message, char *var)
{
	printf("%s %s\n", log_message, var);
}

void	log_list(t_token *token_list)
{
	t_token	*ptr;

	ptr = token_list;
	while (ptr->next != NULL)
	{
		printf("[val: %s | type: %s | quotes: %d] -> ", ptr->value,
			get_token_type(ptr->type), ptr->quotes);
		ptr = ptr->next;
	}
	printf("[val: %s | type: %s | quotes: %d]", ptr->value,
		get_token_type(ptr->type), ptr->quotes);
	printf("\n");
}

void	log_split(char **arr)
{
	size_t	i;

	i = 0;
	printf("split view: {");
	while (i < arr_len(arr))
	{
		printf("[");
		printf("%s", arr[i]);
		printf("]");
		i++;
	}
	printf("}\n");
}

static char	*get_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == REDIR_OUT_APPEND)
		return ("REDIR_OUT_APPEND");
	else if (type == READ_TO_DELIM)
		return ("READ_TO_DELIM");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else if (type == ERROR)
		return ("ERROR");
	else
		return ("UNKNOWN TOKEN TYPE");
}
