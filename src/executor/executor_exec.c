/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:52 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/19 13:00:02 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable(char *cmd, t_env *env);
static char	*resolve_direct_path(char *cmd);
static char	*search_path_directories(char *cmd, char **paths);
void		exec_cmd(t_cmd *cmd, t_env *env);

void	child_exec(t_cmd *cmd, t_exec_params *exec_params)
{
	t_env	*local_env;

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
		exit(exec_builtin(cmd, &local_env, exec_params->last_status));
	}
	exec_cmd(cmd, exec_params->env);
}

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	envp = env_to_array(env);
	if (!cmd->argv[0])
		exit(0);
	path = find_executable(cmd->argv[0], env);
	if (!path)
	{
		ft_putstr_fd("xiaoBij: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	ft_putstr_fd("xiaoBij: ", 1);
	ft_putstr_fd(cmd->argv[0], 1);
	ft_putendl_fd(": Is a directory", 1);
	free_all(envp);
	free(path);
	exit(126);
}

static char	*find_executable(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_val;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (resolve_direct_path(cmd));
	path_val = env_get(env, "PATH");
	if (!path_val)
		return (NULL);
	paths = ft_split(path_val, ':');
	if (!paths)
		return (NULL);
	result = search_path_directories(cmd, paths);
	free_all(paths);
	return (result);
}

static char	*resolve_direct_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_path_directories(char *cmd, char **paths)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = ft_strjoin_free(ft_strjoin(paths[i], "/"), ft_strdup(cmd));
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
