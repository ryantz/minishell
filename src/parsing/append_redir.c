/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:13:16 by fkoh              #+#    #+#             */
/*   Updated: 2026/07/08 16:13:21 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*ptr;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	ptr = cmd->redirs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = redir;
}
