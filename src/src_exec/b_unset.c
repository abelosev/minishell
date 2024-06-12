/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:04:59 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 22:05:17 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//voir pour le prmier et last node
//okay dans la fonction mais modifeir **env_lst pour aller au next

int	builtin_unset(t_group *group, t_list_env **env_lst)
{
	int			i;
	t_list_env	*tmp;
	t_list_env	*next;

	i = 1;
	tmp = *env_lst;
	if (tab_size(group->cmd) == 1)
		return (0);
	while (group->cmd[i])
	{
		if (ft_strncmp((*env_lst)->key, group->cmd[i], \
										ft_strlen((*env_lst)->key)) != 0)
		{
			*env_lst = check_var(env_lst, group->cmd[i]);
			if (*env_lst != NULL)
			{
				next = (*env_lst)->next->next;
				remove_var(&(*env_lst)->next);
				(*env_lst)->next = next;
			}
		}
		else
		{
			tmp = remove_first(env_lst);
		}
		*env_lst = tmp;
		i++;
	}
	return (0);
}
