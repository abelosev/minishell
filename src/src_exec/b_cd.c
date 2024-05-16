/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:56:12 by memarign          #+#    #+#             */
/*   Updated: 2024/05/11 03:02:55 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

// change $OLDPWD

int	builtin_cd(t_group *group, char *path, t_list_env *env_lst)
{
	if (tab_size(group->cmd) > 2)
		return (2);
	if (ft_strncmp(group->cmd[0], "cd", 2) == 0)
	{
		if (tab_size(group->cmd) == 1 \
			|| ft_strncmp(group->cmd[1], "~", 1) == 0)
			path = set_path(env_lst, "HOME");
		else if (ft_strncmp(group->cmd[1], "-", 1) == 0)
		{
			path = set_path(env_lst, "OLDPWD");
			ft_putstr(path);
			write(1, "\n", 1);
		}
		if (chdir(path) == -1)
			return (3);
		//$OLDPWD = path
		return (0);
	}
	// free(path);
	return (4);
}
