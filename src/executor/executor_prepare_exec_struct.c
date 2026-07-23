/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_prepare_exec_struct.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 13:01:01 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 08:22:37 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	prepare_exec_struct(t_cmd *cmd, int prev_fd, int *fd,
			t_exec_params *exec_params)
{
	if (cmd->next && pipe(fd) == -1)
		return (E_FALSE);
	exec_params->prev_fd = prev_fd;
	if (cmd->next)
		exec_params->pipe_fd = fd;
	else
		exec_params->pipe_fd = NULL;
	return (E_TRUE);
}
