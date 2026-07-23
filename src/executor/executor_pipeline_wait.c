/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline_wait.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 08:05:25 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 09:07:25 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal_flag(int signal_recieved, int signaled_status);
static int	status_to_exit_code(int last_status);

int	wait_all_children(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	waited;
	int		signal_received;
	int		signaled_status;

	last_status = 0;
	signal_received = 0;
	signaled_status = 0;
	waited = wait(&status);
	while (waited > 0)
	{
		if (waited == last_pid)
			last_status = status;
		if (WIFSIGNALED(status))
		{
			signal_received = WTERMSIG(status);
			signaled_status = status;
		}
		waited = wait(&status);
	}
	handle_signal_flag(signal_received, signaled_status);
	return (status_to_exit_code(last_status));
}

static void	handle_signal_flag(int signal_received, int signaled_status)
{
	if (signal_received == SIGINT)
	{
		write(1, "\n", 1);
		g_sigint_flag = SIGINT;
	}
	else if (signal_received == SIGQUIT)
	{
		if (WCOREDUMP(signaled_status))
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else
			ft_putstr_fd("Quit\n", STDERR_FILENO);
	}
}

static int	status_to_exit_code(int last_status)
{
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (1);
}
