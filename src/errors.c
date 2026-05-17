#include "minishell.h"

void	write_err(char *err_msg);
void	print_error(t_error err_flag);

int		error_checks(int argc)
{
	if (argc > 1)
		return (print_error(WRONG_ARG_COUNT), 1);
	return (0);
}

void	print_error(t_error err_flag)
{
	if (err_flag == WRONG_ARG_COUNT)
		write_err("Wrong argument count. Just run the executable ./minishell");
}

void	write_err(char *err_msg)
{
	int	len;

	len = ft_strlen(err_msg);
	write(2, err_msg, len);
	write(2, "\n", 1);
}
