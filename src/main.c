/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:18:09 by ryatan            #+#    #+#             */
/*   Updated: 2026/07/07 14:52:25 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_prompt	machine_info;
	char		*prompt;

	if (error_checks(argc, argv) == E_FALSE)
		return (1);
	prompt = prompt_build(&machine_info);
	if (prompt_loop(prompt))
		return (1);
	free(prompt);
	return (0);
}
