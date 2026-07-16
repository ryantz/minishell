/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/16 02:47:34 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	if (error_checks(argc, argv) == E_FALSE)
		return (1);
	env = env_init(envp);
	if (!env)
		return (write_err("Failed to initialize environment\n"), 1);
	if (prompt_loop("tiny-> ", &env))
		return (1);
	free_env(env);
	return (0);
}
