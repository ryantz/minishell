#include "minishell.h"

void	exec_report_error(char *cmd, t_exec_err err)
{
	ft_putstr_fd("xiaoBij: ", 2);
	ft_putstr_fd(cmd, 2);
	if (err == EXEC_NOT_FOUND)
		ft_putendl_fd(": command not found", 2);
	else if (err == EXEC_IS_DIR)
		ft_putendl_fd(": Is a directory", 2);
	else if (err == EXEC_PERM_DENIED)
		ft_putendl_fd(": Permission denied", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
	if (err == EXEC_IS_DIR || err == EXEC_PERM_DENIED)
		exit(126);
	exit(127);
}

void	exec_report_errno(char *cmd)
{
	ft_putstr_fd("xiaoBij: ", 2);
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied", 2);
	else if (errno == EISDIR)
		ft_putendl_fd(": Is a directory", 2);
	else if (errno == ENOEXEC)
		ft_putendl_fd(": Exec format error", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		exit(126);
	exit(127);
}