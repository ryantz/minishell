#include "minishell.h"

char	*get_hostname(const char *PATH);

int	prompt_loop(const char *prompt)
{
	char	*rl_return;
	char	**input_split;

	while (1)
	{
		rl_return = readline(prompt);
		//log_print("String read from prompt:", rl_return);
		input_split = ft_split(rl_return, ' ');
		if (!input_split)
		{
			free_all(input_split);
			return (1);
		}
		//log_split(input_split);
		if (!rl_return)
		{
			perror("Error-> readline() returns NULL");
			return (1);
		}
	}
	return (0);
}

// TODO: expand the prompts as it goes into diff paths
// ryatan@c1r6s2:~/path/$ 
char	*prompt_build(t_prompt *machine_info)
{
	char	*prompt;
	size_t	prompt_len;
	size_t	username_len;
	size_t	hostname_len;

	if (!machine_info)
		return (NULL);
	machine_info->username = getenv("USER");
	machine_info->hostname = get_hostname("/etc/hostname");
	if (!machine_info->username || !machine_info->hostname)
		return (NULL);
	username_len = ft_strlen(machine_info->username);
	hostname_len = ft_strlen(machine_info->hostname);
	prompt_len = username_len + 1 + hostname_len + 4;
	prompt = malloc((prompt_len + 1) * sizeof(char));
	if (!prompt)
		return (NULL);
	prompt[username_len] = '@';
	prompt[prompt_len - 1] = ' ';
	prompt[prompt_len - 2] = '$';
	prompt[prompt_len - 3] = '~';
	prompt[prompt_len - 4] = ':';
	prompt[prompt_len] = 0;
	ft_memcpy(prompt, machine_info->username, username_len);
	ft_memcpy(prompt + username_len + 1, machine_info->hostname, hostname_len);
	return (prompt);
}

char	*get_hostname(const char *PATH)
{
	int		fd;
	int		bytes_read;
	char	*buffer;
	char	**split;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (NULL);
	buffer = malloc(100 * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, 100);
	if (bytes_read <= 0)
		return (NULL);
	split = ft_split(buffer, '.');
	return (split[0]);
}
