/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:22 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 21:54:49 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirs(t_redir *redirs);
static void	free_cmds(t_cmd *cmds);

void	free_pipelines(t_pipeline *pipelines)
{
	t_pipeline	*tmp;

	while (pipelines)
	{
		tmp = pipelines->next;
		free_cmds(pipelines->cmds);
		free(pipelines);
		pipelines = tmp;
	}
}

static void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmds)
	{
		tmp = cmds->next;
		i = 0;
		while (cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		free(redirs->target);
		free(redirs);
		redirs = tmp;
	}
}
