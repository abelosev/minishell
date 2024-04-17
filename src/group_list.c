/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:25 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/17 00:46:27 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

int	get_group_nb(t_tokens *list)
{
	int	group_nb;

	group_nb = 1;
	while (list != NULL)
	{
		if (list->type == 5)
			group_nb++;
		list = list->next;
	}
	return (group_nb);
}

t_tokens	*move_after_pipe(t_tokens *list)
{
	while (list->type != 5 && list->next != NULL)
		list = list->next;
	return (list->next);
}

t_group	*get_group(t_tokens *list, t_list_env *env)
{
	char		**new_envp;
	t_tokens	*start;
	t_group		*group; //static + проверка на NULL

	start = list;
	group = create_init_group();
	group->cmd = get_cmd_tab(list);
	if (!group->cmd)
		invalid_group(group, 1);
	if (is_built(group->cmd[0]) == 0)
	{
		new_envp = get_envp(env);
		group->cmd[0] = cmd_check(group->cmd, new_envp);
		if (group->cmd[0] == NULL)
		{
			free(group->cmd);
			invalid_group(group, 127); //cmd not found
			ft_putstr_err("Command not found\n");
		}
		free_tab(new_envp);
	}
	list = start;
	if (get_files(list, group) != 0)
		invalid_group(group, 1);
	return (group);
}

void get_new_node(t_tokens *list, t_list_env *env, t_group *begin_gr, t_group *curr_gr)
{
	list = move_after_pipe(list);
	if (list == NULL)
		return ;		
	begin_gr->next = get_group(list, env);
	if (!begin_gr->next)
	{
		free_group_list(curr_gr);
		return ;
	}
	begin_gr = begin_gr->next;
}

t_group	*get_group_list(t_tokens *list, t_list_env *env)
{
	t_group	*begin_gr;
	t_group	*curr_gr;

	begin_gr = get_group(list, env);
	if (!begin_gr)
		return (NULL);
	if (get_group_nb(list) == 1)
		return (begin_gr);
	else
	{
		curr_gr = begin_gr;
		while (get_group_nb(list))
		{
            // list = move_after_pipe(list);//мб избыточно, учитывая условие while
			// if (list == NULL) //должно входить в проверку синтаксиса раньше
			// 	break ;		
			// begin_gr->next = get_group(list, env);
			// if (!begin_gr->next)
			// {
			// 	free_group_list(curr_gr);
			// 	break ;
			// }
			// begin_gr = begin_gr->next;

			get_new_node(list, env, begin_gr, curr_gr);
		}
	}
	return (curr_gr); //change to begin_gr
}
