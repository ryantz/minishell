/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:52 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 21:17:42 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable(char *cmd, t_env *env);
void		exec_cmd(t_cmd *cmd, t_env *env);

void	child_exec(t_cmd *cmd, int prev_fd, int *pipe_fd, t_env *env)
{
	t_env	*local_env;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pipe_fd)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (apply_redirs(cmd->redirs) == E_FALSE)
		exit(1);
	if (is_builtin(cmd->argv[0]) == E_TRUE)
	{
		local_env = env;
		exit(exec_builtin(cmd, &local_env, 1));
	}
	exec_cmd(cmd, env);
}

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (!cmd->argv[0])
		exit(0);
	path = find_executable(cmd->argv[0], env);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(path, cmd->argv, env_to_array(env));
	exit(126);
}

static char	*find_executable(char *cmd, t_env *env)
{
	char	**paths;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = ft_split(env_get(env, "PATH"), ':');
	if (!paths)
		return (NULL);
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
