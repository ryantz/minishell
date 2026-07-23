/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:10:22 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 09:49:21 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipelines(t_pipeline *pipelines)
{
	t_pipeline	*tmp;

	while (pipelines)
	{
		tmp = pipelines->next;
		free_cmd_list(pipelines->cmds);
		free(pipelines);
		pipelines = tmp;
	}
}
