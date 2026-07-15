/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:13 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/15 18:38:51 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(char *line, t_env **env, int last_status);
static int	handle_eof(int last_status);

int	prompt_loop(const char *prompt, t_env **env)
{
	char	*rl_return;
	int		last_status;

	init_signals();
	last_status = 0;
	while (1)
	{
		rl_return = readline(prompt);
		if (!rl_return)
			return (handle_eof(last_status));
		if (*rl_return == '\0')
		{
			free(rl_return);
			continue ;
		}
		add_history(rl_return);
		last_status = process_line(rl_return, env, last_status);
		free(rl_return);
	}
	return (last_status);
}

static int	handle_eof(int last_status)
{
	printf("exit\n");
	return (last_status);
}

static int	process_line(char *line, t_env **env, int last_status)
{
	t_token		*token_list;
	t_pipeline	*pipelines;

	token_list = create_token_list(line, *env, last_status);
	if (!token_list)
		return (last_status);
	pipelines = parse_tokens(token_list);
	free_token_list(token_list);
	if (!pipelines)
	{
		write_err("syntax error");
		return (2);
	}
	last_status = evaluate_pipeline(pipelines, env);
	free_pipelines(pipelines);
	return (last_status);
}
