/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:56 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/17 00:00:00 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	fork_one_cmd(t_cmd *cmd, int prev_fd, int *pipe_fd, t_env *env);
static int		wait_all_children(pid_t last_pid);
static int		run_builtin_with_redirs(t_cmd *cmd, t_env **env);

int	run_pipeline(t_pipeline *pipeline, t_env **env)
{
	t_cmd	*cmd;
	int		prev_fd;
	int		fd[2];
	pid_t	last_pid;

	cmd = pipeline->cmds;
	if (!cmd->next && is_builtin(cmd->argv[0]) == E_TRUE)
		return (run_builtin_with_redirs(cmd, env));
	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (-1);
		last_pid = fork_one_cmd(cmd, prev_fd, cmd->next ? fd : NULL, *env);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	return (wait_all_children(last_pid));
}

static int	run_builtin_with_redirs(t_cmd *cmd, t_env **env)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs) == E_FALSE)
		status = 1;
	else
		status = exec_builtin(cmd, env, 0);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (status);
}

static pid_t	fork_one_cmd(t_cmd *cmd, int prev_fd, int *pipe_fd, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_exec(cmd, prev_fd, pipe_fd, env);
	return (pid);
}

static int	wait_all_children(pid_t last_pid)
{
	int		status;
	pid_t	waited;

	status = 0;
	waited = wait(&status);
	while (waited > 0)
	{
		if (waited == last_pid)
			break ;
		waited = wait(&status);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
