/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_m_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:55:42 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 22:20:24 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void close_fds(t_exec *exec)
{
    if (exec->pfd_in > 0)
    {
        close(exec->pfd_in);
        exec->pfd_in = -1; // Reset to indicate closed descriptor
    }
    if (exec->pfd_out > 0)
    {
        close(exec->pfd_out);
        exec->pfd_out = -1; // Reset to indicate closed descriptor
    }
}

void minish(t_exec *exec, t_group *group, t_list_env **env)
{
    while (group != NULL)
    {
        if (group->flag_fail != 0)
        {
            reset_minish(exec);
            // print error msgs
            break;
        }
        else if (group->flag_fail == 0)
        {
            if (group->next != NULL)
                ft_pipe(exec);
            simple_cmd(exec, group, env);
            // Wait for the child process to finish
            waitpid(-1, NULL, 0);
            close_fds(exec);
        }
        group = group->next;
    }
}

void	reset_minish(t_exec *exec)
{
	close_fds(exec);
	init_exec(exec);
	// set_io(exec);
}
