/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:56 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 10:40:58 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	run_if_single_cmd(t_cmd *cmd, t_single_cmd_params *s_cmd);
static t_status	read_all_heredocs(t_cmd *cmds, t_env *env, int last_status);
static int		run_builtin_with_redirs(t_cmd *cmd, t_env **env,
					int last_status, int *should_exit);
static int		status_after_pipeline(pid_t last_pid);

int	run_pipeline(t_pipeline *pipeline, t_env **env, int last_status,
			int *s_e)
{
	t_cmd				*cmd;
	pid_t				last_pid;
	t_single_cmd_params	s_cmd;

	cmd = pipeline->cmds;
	s_cmd.env = env;
	s_cmd.last_status = last_status;
	s_cmd.should_exit = s_e;
	if (run_if_single_cmd(cmd, &s_cmd) == E_TRUE)
		return (s_cmd.out_status);
	if (read_all_heredocs(cmd, *env, last_status) == E_FALSE)
		return (1);
	signal(SIGINT, SIG_IGN);
	last_pid = run_pipeline_cmds(cmd, *env, last_status);
	if (last_pid == -1)
	{
		wait_all_children(-1);
		signal(SIGINT, sigint_handler);
		return (1);
	}
	return (status_after_pipeline(last_pid));
}

static t_status	run_if_single_cmd(t_cmd *cmd, t_single_cmd_params *s_cmd)
{
	if (cmd->next)
		return (E_FALSE);
	if (handle_sole_assignments(cmd, s_cmd->env) == E_TRUE)
	{
		s_cmd->out_status = 0;
		return (E_TRUE);
	}
	if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]) == E_TRUE)
	{
		if (read_heredocs(cmd->redirs, *s_cmd->env,
				s_cmd->last_status) == E_FALSE)
			s_cmd->out_status = 1;
		else
			s_cmd->out_status = run_builtin_with_redirs(cmd, s_cmd->env,
					s_cmd->last_status, s_cmd->should_exit);
		return (E_TRUE);
	}
	return (E_FALSE);
}

static t_status	read_all_heredocs(t_cmd *cmds, t_env *env, int last_status)
{
	while (cmds)
	{
		if (read_heredocs(cmds->redirs, env, last_status) == E_FALSE)
			return (E_FALSE);
		cmds = cmds->next;
	}
	return (E_TRUE);
}

static int	run_builtin_with_redirs(t_cmd *cmd, t_env **env, int last_status,
			int *should_exit)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs) == E_FALSE)
		status = 1;
	else
		status = exec_builtin(cmd, env, last_status, should_exit);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (status);
}

static int	status_after_pipeline(pid_t last_pid)
{
	int	status;

	status = wait_all_children(last_pid);
	signal(SIGINT, sigint_handler);
	return (status);
}
