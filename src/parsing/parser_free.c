/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:13:42 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/08 16:13:43 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//shared recursive cleanup

void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmds)
	{
		tmp = cmds->next;
		i = 0;
		while (cmds->argv && cmds->argv[i])
			free(cmds->argv[i++]);
		free(cmds->argv);
		free_redirs_local(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

void	free_redirs_local(t_redir *redirs)
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
