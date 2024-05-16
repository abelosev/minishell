/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:56:38 by memarign          #+#    #+#             */
/*   Updated: 2024/05/11 02:56:39 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//function is_option?
// echo \n word = \n word (sgould not print \)

int	builtin_echo(t_group *group)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (tab_size(group->cmd) < 2)
		write(1, "\n", 1);
	else
	{
		if (ft_strncmp(group->cmd[i], "-n", 2) == 0 \
										&& is_char(group->cmd[i], 'n'))
		{
			option = 1;
			i++;
		}
		while (group->cmd[i])
		{
			ft_putstr(group->cmd[i]);
			if (group->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		if (!option)
			write(1, "\n", 1);
	}
	return (0);
}
