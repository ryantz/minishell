/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/24 00:18:10 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_prompt	machine_info;
	char		*prompt;

	prompt = prompt_build(&machine_info);
	error_checks(argc, argv);
	if (prompt_loop(prompt))
		return (1);
	free(prompt);
	return (0);
}
