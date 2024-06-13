/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:56:38 by memarign          #+#    #+#             */
/*   Updated: 2024/06/11 20:10:25 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//function is_option?
// echo \n word = \n word (sgould not print \)

int	builtin_echo(t_group *group, t_built *fd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (tab_size(group->cmd) < 2)
		write(fd->out, "\n", 1);
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
			ft_fd_putstr(group->cmd[i], fd->out);
			// if (group->cmd[i + 1] != NULL)
			// 	write(fd->out, " ", 1);
			i++;
		}
		if (!option)
			write(fd->out, "\n", 1);
	}
	return (0);
}
