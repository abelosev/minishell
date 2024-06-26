/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:09:37 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:09:45 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signum)
{
	g_status = signum;
	write(2, "Quit (core dumped)\n", 19);
	return ;
}

static int	check_rl_done(void)
{
	return (0);
}

static void	parent_signal_handler(int signal)
{
	g_status = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_done = 1;
}

void	parent_signal(void)
{
	rl_event_hook = check_rl_done;
	signal(SIGINT, &parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
