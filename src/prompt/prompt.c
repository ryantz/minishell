/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:13 by ryatan            #+#    #+#             */
/*   Updated: 2026/06/01 16:12:11 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(const char *PATH);
void	create_prompt(t_prompt *machine_info, char **prompt);

int	prompt_loop(const char *prompt)
{
	char	*rl_return;
	t_token	*token_list;

	init_signals();
	rl_catch_signals = 0;
	while (1)
	{
		rl_return = readline(prompt);
		g_signal = 0;
		if (!rl_return)
		{
			printf("exit\n");
			break;
		}
		if (*rl_return == '\0')
		{
			free(rl_return);
			continue;
		}
		add_history(rl_return);
		log_print("String read from prompt:\n", rl_return);
		token_list = create_token_list(rl_return);
		free(rl_return);
		if (!token_list)
			return (1);
		log_list(token_list);
		// add a free here
	}
	return (0);
}

// NOTE: getenv() might not work with command export
char	*prompt_build(t_prompt *machine_info)
{
	char	*prompt;

	if (!machine_info)
		return (NULL);
	machine_info->username = getenv("USER");
	machine_info->hostname = get_hostname("/etc/hostname");
	machine_info->path = getenv("PWD");
	if (!machine_info->username || !machine_info->hostname)
		return (NULL);
	machine_info->username_len = ft_strlen(machine_info->username);
	machine_info->hostname_len = ft_strlen(machine_info->hostname);
	machine_info->path_len = ft_strlen(machine_info->path);
	machine_info->prompt_len = machine_info->username_len + 1
		+ machine_info->hostname_len + 1 + machine_info->path_len + 3;
	create_prompt(machine_info, &prompt);
	free(machine_info->hostname);
	return (prompt);
}

void	create_prompt(t_prompt *machine_info, char **prompt)
{
	*prompt = malloc((machine_info->prompt_len + 1) * sizeof(char));
	if (!*prompt)
		return ;
	ft_memcpy(*prompt, machine_info->username, machine_info->username_len);
	ft_memcpy(*prompt + machine_info->username_len + 1, machine_info->hostname,
		machine_info->hostname_len);
	ft_memcpy(*prompt + machine_info->username_len + 1
		+ machine_info->hostname_len + 2, machine_info->path,
		machine_info->path_len);
	(*prompt)[machine_info->username_len] = '@';
	(*prompt)[machine_info->prompt_len - 1] = ' ';
	(*prompt)[machine_info->prompt_len - 2] = '$';
	(*prompt)[machine_info->prompt_len] = 0;
	(*prompt)[machine_info->username_len
		+ machine_info->hostname_len + 1] = ':';
	(*prompt)[machine_info->username_len
		+ machine_info->hostname_len + 2] = '~';
}

char	*get_hostname(const char *PATH)
{
	int		fd;
	int		bytes_read;
	char	*buffer;
	char	**split;
	char	*hostname;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = malloc(100 * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, 100);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	split = ft_split(buffer, '.');
	free(buffer);
	if (!split)
		return (NULL);
	hostname = ft_strdup(split[0]);
	free_all(split);
	return (hostname);
}
