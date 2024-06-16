/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:02 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/16 03:14:01 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_is_flag(char *str)
{
	int	i;

	if ((ft_strlen(str) < 2) || (ft_strncmp(str, "-n", 2) != 0))
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_group *group, int fd)
{
	int	option_flag;
	int	i;

	if (group->cmd[1] == NULL)
	{
		write(fd, "\n", 1);
		return (0);
	}
	option_flag = 0;
	i = 1;
	while (group->cmd[i] && ft_echo_is_flag(group->cmd[i]))
	{
		option_flag = 1;
		i++;
	}
	while (group->cmd[i])
	{
		write(fd, group->cmd[i], ft_strlen(group->cmd[i]));
		i++;
		if (group->cmd[i])
			write(fd, " ", 1);
	}
	if (option_flag == 0)
		write(fd, "\n", 1);
	return (0);
}
