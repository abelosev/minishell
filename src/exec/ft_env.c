/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:04:39 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/26 18:04:42 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_group *group, t_list_env *env, int fd)
{
	if (group->cmd[1] && *(group->cmd[1])
		&& (ft_strncmp(group->cmd[1], "env", ft_strlen("env"))))
	{
		ft_putstr_err("env : ");
		ft_putstr_err(group->cmd[1]);
		ft_putstr_err(": No such file or directory\n");
		return (127);
	}
	print_env_list(env, fd);
	return (0);
}
