/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoh <fkoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:52:53 by fkoh              #+#    #+#             */
/*   Updated: 2026/06/01 16:12:12 by fkoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

volatile sig_atomic_t g_signal = 0;

void sigint_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void init_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");

	signal(SIGQUIT, SIG_IGN);
}
