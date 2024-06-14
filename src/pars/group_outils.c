/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:47:14 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/14 04:29:56 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	invalid_group(t_group *group, int flag)
{
	group->flag_fail = flag;
	group->cmd = NULL;
	group->redir_in = NULL;
	group->redir_out = NULL;
	group->app_out = NULL;
	group->app_in = NULL;
	group->next = NULL;
}

t_group	*create_init_group(void)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group || group == NULL)
		return (NULL);
	invalid_group(group, 0);
	return (group);
}

t_group	*cmd_not_null(t_group *group, int flag, t_tokens *start)
{
	if (flag > 0)
	{
		free_tab(group->cmd);
		invalid_group(group, flag);
	}
	else
	{
		if (group->cmd && group->cmd[0] != NULL && group->cmd[0][0] != '\0'
			&& get_files(start, group) != 0)
		{
			free_tab(group->cmd);
			invalid_group(group, 1);
		}
	}
	return (group);
}

t_group	*get_group(t_tokens *list, t_list_env *env)
{
	t_tokens	*start;
	t_group		*group;
	int			flag;

	start = list;
	group = create_init_group();
	group->cmd = get_cmd_tab(list);
	if (!group->cmd)
	{
		list = start;
		if (get_files(list, group) != 0)
			invalid_group(group, 1);
		return (group);
	}
	flag = cmd_check(&(group->cmd[0]), env);
	return (cmd_not_null(group, flag, start));
}
