/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_fork.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 10:12:48 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 10:40:21 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		cleanup_pipe_fds(int prev_fd, int *fd, int has_next);
static void		advance_pipeline_fd(int *prev_fd, int *fd, t_cmd *cmd);
static pid_t	fork_one_cmd(t_cmd *cmd, t_exec_params *exec_params);

pid_t	run_pipeline_cmds(t_cmd *cmd, t_env *env, int last_status)
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
		if (prepare_exec_struct(cmd, prev_fd, fd, &exec_params) == E_FALSE)
			return (cleanup_pipe_fds(prev_fd, fd, 0), -1);
		last_pid = fork_one_cmd(cmd, &exec_params);
		if (last_pid == -1)
			return (cleanup_pipe_fds(prev_fd, fd, cmd->next != NULL), -1);
		advance_pipeline_fd(&prev_fd, fd, cmd);
		cmd = cmd->next;
	}
	return (close(prev_fd), last_pid);
}

static void	advance_pipeline_fd(int *prev_fd, int *fd, t_cmd *cmd)
{
	close(*prev_fd);
	*prev_fd = -1;
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

static void	cleanup_pipe_fds(int prev_fd, int *fd, int has_next)
{
	if (has_next)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (prev_fd != -1)
		close(prev_fd);
}

static pid_t	fork_one_cmd(t_cmd *cmd, t_exec_params *exec_params)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		write_err("xiaoBij: fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_exec(cmd, exec_params);
	}
	return (pid);
}
