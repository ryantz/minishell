#include "minishell.h"

t_status	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (E_FALSE);
	if (ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0)
		return (E_TRUE);
	return (E_FALSE);
}

int	exec_builtin(t_cmd *cmd, t_env **env, int last_status)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, env));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(*env));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv, last_status));
	return (1);
}
