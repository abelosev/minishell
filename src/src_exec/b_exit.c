/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:04:38 by memarign          #+#    #+#             */
/*   Updated: 2024/06/04 11:04:39 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//end the process
//process then only contain return exec->status
//go to parent or end shell

int	end_minish(t_exec *exec, t_group *group, t_list_env *env)
{
	if (group != NULL)
		free_group_list(group);
	if (env != NULL)
		free_envp_list(env);
	close_fds(exec);
	init_exec(exec);
	clear_history();
	// if (status == 0)
	// 	exit(EXIT_SUCCESS); //use tty?
	// else
	return (status);
}

void	builtin_error(t_exec *exec, t_group *group)
{
	if (exec->stat == 1)
	{
		ft_putstr_fd("minishell", group->cmd[0], 2);
		//cmd not found
	}
	if (exec->stat == 2)
	{
		ft_putstr_fd("minishell", group->cmd[0], 2);
		//too many arguments
	}
	else if (exec->stat == 3)
	{
		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
		// //invalid option
	}
	else if (exec->stat == 126)
	{
		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
		//wrong path
	}
	else if (exec->stat == 127)
		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
}

// void	builtin_exit(t_exec *exec, t_group *group, t_list_env *env)
// {
// 	if (exec->status == 2)
// 	{
// 		ft_putstr_fd("minishell", group->cmd[0], 2);
// 		//too many arguments
// 	}
// 	else if (exec->status == 3)
// 	{
// 		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
// 		//wrong path
// 	}
// 	else if (exec->status == 4)
// 		ft_putstr_fd(group->cmd[0], ": Command failed\n", 2);
// 	else if (exec->status == 5)
// 	{
// 		ft_putstr_fd(group->cmd[0], group->cmd[1], 2);
// 		// //invalid option
// 	}
// 	end_minish(exec, group, env);
// }
