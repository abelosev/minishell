/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:04:44 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 22:00:22 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//format reçu?
int	builtin_export(t_group *group, t_list_env **env_lst)
{
	int			i;
	t_list_env	*tmp;

	i = 1;
	tmp = *env_lst;
	if (tab_size(group->cmd) == 1)
		print_env_list(*env_lst, fd);
	else
	{
		while (group->cmd[i])
		{
			if (ft_strncmp((*env_lst)->key, group->cmd[i], ft_strlen((*env_lst)->key)) != 0)
			{
				*env_lst = check_var(env_lst, group->cmd[i]);
				if (*env_lst)
					*env_lst = (*env_lst)->next;
			}
			mod_var(env_lst, group->cmd[i], tmp);
			*env_lst = tmp;
			i++;
		}
	}
	return (0);
}
//change strncmp