/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:52 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 09:08:35 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable(char *cmd, t_env *env, t_exec_err *err);
static char	*resolve_direct_path(char *cmd, t_exec_err *err);
static char	*search_path_directories(char *cmd, char **paths, t_exec_err *err);
void		exec_cmd(t_cmd *cmd, t_env *env);

void	child_exec(t_cmd *cmd, t_exec_params *exec_params)
{
	t_env	*local_env;
	int		should_exit;

	if (exec_params->prev_fd != -1)
	{
		dup2(exec_params->prev_fd, STDIN_FILENO);
		close(exec_params->prev_fd);
	}
	if (exec_params->pipe_fd)
	{
		dup2(exec_params->pipe_fd[1], STDOUT_FILENO);
		close(exec_params->pipe_fd[0]);
		close(exec_params->pipe_fd[1]);
	}
	if (apply_redirs(cmd->redirs) == E_FALSE)
		exit(1);
	if (is_builtin(cmd->argv[0]) == E_TRUE)
	{
		local_env = exec_params->env;
		should_exit = 0;
		exit(exec_builtin(cmd, &local_env, exec_params->last_status,
				&should_exit));
	}
	exec_cmd(cmd, exec_params->env);
}

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char		*path;
	char		**envp;
	t_exec_err	err;

	if (!cmd->argv[0])
		exit(0);
	path = find_executable(cmd->argv[0], env, &err);
	if (!path)
		exec_report_error(cmd->argv[0], err);
	envp = env_to_array(env);
	execve(path, cmd->argv, envp);
	free(path);
	free_all(envp);
	exec_report_errno(cmd->argv[0]);
}

static char	*find_executable(char *cmd, t_env *env, t_exec_err *err)
{
	char	**paths;
	char	*path_val;
	char	*result;

	*err = EXEC_NOT_FOUND;
	if (!cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (resolve_direct_path(cmd, err));
	path_val = env_get(env, "PATH");
	if (!path_val)
	{
		*err = EXEC_NO_SUCH_FILE;
		return (NULL);
	}
	paths = ft_split(path_val, ':');
	if (!paths)
		return (NULL);
	result = search_path_directories(cmd, paths, err);
	free_all(paths);
	return (result);
}

static char	*resolve_direct_path(char *cmd, t_exec_err *err)
{
	struct stat	st;

	if (stat(cmd, &st) != 0)
	{
		*err = EXEC_NO_SUCH_FILE;
		return (NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		*err = EXEC_IS_DIR;
		return (NULL);
	}
	if (access(cmd, X_OK) != 0)
	{
		*err = EXEC_PERM_DENIED;
		return (NULL);
	}
	*err = EXEC_FOUND;
	return (ft_strdup(cmd));
}

static char	*search_path_directories(char *cmd, char **paths, t_exec_err *err)
{
	char	*full;
	int		i;
	int		found_not_exec;

	i = 0;
	found_not_exec = 0;
	while (paths[i])
	{
		full = ft_strjoin_free(ft_strjoin(paths[i], "/"), ft_strdup(cmd));
		if (access(full, F_OK) == 0)
		{
			if (access(full, X_OK) == 0)
				return (*err = EXEC_FOUND, full);
			found_not_exec = 1;
		}
		free(full);
		i++;
	}
	if (found_not_exec)
		*err = EXEC_PERM_DENIED;
	else
		*err = EXEC_NOT_FOUND;
	return (NULL);
}
