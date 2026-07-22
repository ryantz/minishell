/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:56 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/19 13:07:31 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	fork_one_cmd(t_cmd *cmd, t_exec_params *exec_params);
static int		wait_all_children(pid_t last_pid);
static int		run_builtin_with_redirs(t_cmd *cmd, t_env **env,
					int last_status);
static pid_t	run_pipeline_cmds(t_cmd *cmd, t_env *env, int last_status);

int	run_pipeline(t_pipeline *pipeline, t_env **env, int last_status)
{
	t_cmd	*cmd;
	pid_t	last_pid;
	int status;

	cmd = pipeline->cmds;
	if (!cmd->next && is_builtin(cmd->argv[0]) == E_TRUE)
	{
		if (read_heredocs(cmd->redirs, *env, last_status) == E_FALSE)
			return (1);
		return (run_builtin_with_redirs(cmd, env, last_status));
	}
	signal(SIGINT, SIG_IGN);
	last_pid = run_pipeline_cmds(cmd, *env, last_status);
	if (last_pid == -1)
	{
		signal(SIGINT, sigint_handler);
		return (1);
	}
	status = wait_all_children(last_pid);
	signal(SIGINT, sigint_handler);
	return (wait_all_children(last_pid));
}

static pid_t	run_pipeline_cmds(t_cmd *cmd, t_env *env, int last_status)
{
	int				prev_fd;
	int				fd[2];
	pid_t			last_pid;
	t_exec_params	exec_params;

	prev_fd = -1;
	exec_params.env = env;
	exec_params.last_status = last_status;
	while (cmd)
	{
		if (read_heredocs(cmd->redirs, env, last_status) == E_FALSE)
			return (-1);
		if (prepare_exec_struct(cmd, prev_fd, fd, &exec_params) == E_FALSE)
			return (-1);
		last_pid = fork_one_cmd(cmd, &exec_params);
		close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	close(prev_fd);
	return (last_pid);
}

static int	run_builtin_with_redirs(t_cmd *cmd, t_env **env, int last_status)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs) == E_FALSE)
		status = 1;
	else
		status = exec_builtin(cmd, env, last_status);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (status);
}

static pid_t	fork_one_cmd(t_cmd *cmd, t_exec_params *exec_params)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_exec(cmd, exec_params);
	}
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
