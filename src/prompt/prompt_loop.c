/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:13 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/23 10:44:57 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_prompt(const char *prompt, t_env **env, int interactive,
				int *last_status);
static int	process_line(char *line, t_env **env, int last_status,
				int *should_exit);
static int	handle_eof(int last_status, int interactive);
static int	run_all_pipelines(t_pipeline *pipeline, t_env **env,
				int last_status, int *should_exit);

int	prompt_loop(const char *prompt, t_env **env)
{
	int		last_status;
	int		interactive;
	int		ret;

	init_signals();
	last_status = 0;
	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		ret = process_prompt(prompt, env, interactive, &last_status);
		if (ret != -1)
			return (ret);
	}
}

static int	handle_eof(int last_status, int interactive)
{
	if (interactive)
		ft_putendl_fd("exit", STDOUT_FILENO);
	return (last_status);
}

static int	run_all_pipelines(t_pipeline *pipeline, t_env **env,
		int last_status, int *should_exit)
{
	int	status;
	int	skip;

	status = last_status;
	skip = 0;
	while (pipeline)
	{
		if (!skip)
			status = run_pipeline(pipeline, env, status, should_exit);
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

static int	process_line(char *line, t_env **env, int last_status,
			int *should_exit)
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
	last_status = run_all_pipelines(pipelines, env, last_status, should_exit);
	free_pipelines(pipelines);
	return (last_status);
}

static int	process_prompt(const char *prompt, t_env **env, int interactive,
			int *last_status)
{
	char	*line;
	int		should_exit;

	should_exit = 0;
	line = next_line(prompt, interactive);
	check_sigint_flag(last_status);
	if (!line)
		return (handle_eof(*last_status, interactive));
	if (*line == '\0')
	{
		free(line);
		return (-1);
	}
	if (interactive)
		add_history(line);
	*last_status = process_line(line, env, *last_status, &should_exit);
	free(line);
	if (should_exit)
		return (*last_status);
	return (-1);
}
