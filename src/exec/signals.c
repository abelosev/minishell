/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:14:38 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/24 18:44:21 by abelosev         ###   ########.fr       */
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


// void	ft_sigint(int signal)
// {
// 	(void)signal;
// 	ft_putstr_err("^C\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	g_status = 130;
// }

// void	ft_sigint_hd(int signal)
// {
// 	(void)signal;
// 	close(STDIN_FILENO);
// 	ft_putstr_err("^C\n");
// }

// void ft_sigquit(int signal)
// {
// 	(void)signal;
// 	ft_putstr_err( "Quit (core dumped)\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	g_status = 131;
// }