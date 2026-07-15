#include "minishell.h"

static pid_t	fork_one_cmd(t_cmd *cmd, int prev_fd, int *pipe_fd, t_env *env);
static int		wait_all_children(pid_t last_pid);

int	run_pipeline(t_pipeline *pipeline, t_env *env)
{
	t_cmd	*cmd;
	int		prev_fd;
	int		fd[2];
	pid_t	last_pid;

	prev_fd = -1;
	cmd = pipeline->cmds;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return (-1);
		last_pid = fork_one_cmd(cmd, prev_fd, cmd->next ? fd : NULL, env);
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