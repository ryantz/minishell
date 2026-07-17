/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:13 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/17 00:00:00 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(char *line, t_env **env, int last_status);
static int	handle_eof(int last_status);
static char	*next_line(const char *prompt, int interactive);

int	prompt_loop(const char *prompt, t_env **env)
{
	char	*rl_return;
	int		last_status;
	int		interactive;

	init_signals();
	last_status = 0;
	interactive = isatty(STDIN_FILENO); //this was added
	while (1)
	{
		rl_return = next_line(prompt, interactive);
		if (!rl_return)
			return (handle_eof(last_status));
		if (*rl_return == '\0')
		{
			free(rl_return);
			continue ;
		}
		if (interactive)
			add_history(rl_return);
		last_status = process_line(rl_return, env, last_status);
		free(rl_return);
	}
	return (last_status);
}

static char	*next_line(const char *prompt, int interactive)
{
	if (interactive)
		return (readline(prompt));
	return (read_line_stdin());
}

static int	handle_eof(int last_status)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (last_status);
}

static int	run_all_pipelines(t_pipeline *pipeline, t_env **env)
{
	int	status;

	status = 0;
	while (pipeline)
	{
		status = run_pipeline(pipeline, *env);
		if (pipeline->link_to_next == L_AND && status != 0)
			break ;
		if (pipeline->link_to_next == L_OR && status == 0)
			break ;
		pipeline = pipeline->next;
	}
	return (status);
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
	last_status = run_all_pipelines(pipelines, env);
	free_pipelines(pipelines);
	return (last_status);
}
