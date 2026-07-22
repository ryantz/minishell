/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 18:09:25 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 18:09:26 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_valid_identifier(char *str);
static void		print_export_error(char *arg);
void			export_one(t_env **env, char *arg);

int	builtin_export(char **args, t_env **env)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_sorted_env(*env);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_export_error(args[i]);
			status = 1;
		}
		else
			export_one(env, args[i]);
		i++;
	}
	return (status);
}

void	export_one(t_env **env, char *arg)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		if (key)
			env_set(env, key, ft_strdup(eq + 1));
		free(key);
	}
	else
		env_touch(env, arg);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

t_status handle_sole_assignments(t_cmd *cmd, t_env **env)
{
    int i;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (E_FALSE);

    /* 1. Check if EVERY argument in argv is a valid assignment (e.g. KEY=VAL) */
    i = 0;
    while (cmd->argv[i])
    {
        /* Must contain '=' AND have a valid identifier before '=' */
        if (!ft_strchr(cmd->argv[i], '=') || !is_valid_identifier(cmd->argv[i]))
            return (E_FALSE);
        i++;
    }

    /* 2. All args are assignments! Export them to the shell environment */
    i = 0;
    while (cmd->argv[i])
    {
        export_one(env, cmd->argv[i]);
        i++;
    }
    return (E_TRUE);
}
