/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:14:38 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/17 22:45:19 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putstr_err("^C\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_hd(int signal)
{
	(void)signal;
	close(STDIN_FILENO);
	ft_putstr_err("^C\n");
}
