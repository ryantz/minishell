/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/19 12:22:46 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	int			status;

	if (error_checks(argc, argv) == E_FALSE)
		return (1);
	env = env_init(envp);
	if (!env)
		return (write_err("Failed to initialize environment"), 1);
	status = prompt_loop("tiny-> ", &env);
	free_env(env);
	return (status);
}
