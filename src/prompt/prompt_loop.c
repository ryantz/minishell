/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:13 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/18 21:56:34 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_line(char *line, t_env **env, int last_status);
static int	handle_eof(int last_status, int interactive);
static char	*next_line(const char *prompt, int interactive);
static int	run_all_pipelines(t_pipeline *pipeline, t_env **env,
				int last_status);

int	prompt_loop(const char *prompt, t_env **env)
{
	char	*rl_return;
	int		last_status;
	int		interactive;

	init_signals();
	last_status = 0;
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		rl_return = next_line(prompt, interactive);
		if (g_sigint_flag)
		{
			last_status = 130;
			g_sigint_flag = 0;
		}
		if (!rl_return)
			return (handle_eof(last_status, interactive));
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

static int	handle_eof(int last_status, int interactive)
{
	if (interactive)
		ft_putendl_fd("exit", STDOUT_FILENO);
	return (last_status);
}

static char	*next_line(const char *prompt, int interactive)
{
	if (interactive)
		return (readline(prompt));
	return (read_line_stdin());
}

static int	run_all_pipelines(t_pipeline *pipeline, t_env **env,
		int last_status)
{
	int	status;
	int	skip;

	status = last_status;
	skip = 0;
	while (pipeline)
	{
		if (!skip)
			status = run_pipeline(pipeline, env, status);
		if (pipeline->link_to_next == L_AND)
			skip = (status != 0);
		else if (pipeline->link_to_next == L_OR)
			skip = (status == 0);
		else
			skip = 0;
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
	last_status = run_all_pipelines(pipelines, env, last_status);
	free_pipelines(pipelines);
	return (last_status);
}
