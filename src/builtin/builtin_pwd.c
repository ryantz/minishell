#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[PATH_BUFFER];

	if (!getcwd(cwd, PATH_BUFFER))
		return (1);
	printf("%s\n", cwd);
	return (0);
}