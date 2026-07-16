/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:17:58 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 01:55:13 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **arr)
{
	size_t	i;

	i = 0;
	while (i < arr_len(arr))
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->value);
		free(token_list);
		token_list = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

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
