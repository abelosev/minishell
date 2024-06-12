/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_fd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:31 by memarign          #+#    #+#             */
/*   Updated: 2024/06/04 11:07:32 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	set_io(t_exec *exec)
{
	dup2(exec->fd_in, STDIN_FILENO);
	dup2(exec->fd_out, STDOUT_FILENO);
}

void	init_exec(t_exec *exec)
{
	exec->stat = -1;
	exec->fd_in = -1;
	exec->fd_out = -1;
	exec->pfd_in = -1;
	exec->pfd_out = -1;
	exec->pid = -1;
}
void	reset_fds(t_exec *exec)
{
	if (exec->fd_in > 0)
		close(exec->fd_in);
	exec->fd_in = -1;
	if (exec->fd_out > 0)
		close(exec->fd_out);
	exec->fd_out = -1;
}