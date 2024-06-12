/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_set_io_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:31:13 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 14:46:10 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_cmd **cmd_list, int i, int single_flag)
{
	if (cmd_list[i]->in_fd != 0 && single_flag == 0)
		dup2(cmd_list[i]->in_fd, STDIN_FILENO);
	if (cmd_list[i]->in_fd != 0)
	{
		close(cmd_list[i]->in_fd);
		cmd_list[i]->in_fd = 0;
	}
	if ((cmd_list[i]->out_fd != 1) && single_flag == 0)
	{
		dup2(cmd_list[i]->out_fd, STDOUT_FILENO);
		close(cmd_list[i]->out_fd);
		cmd_list[i]->out_fd = 1;
	}
	if (single_flag == 0)
		ft_close_all(cmd_list);
}

int	ft_hdoc_write(char *str, int *pipe_ends)
{
	if (!str)
		return (1);
	write(pipe_ends[1], str, ft_strlen(str));
	write(pipe_ends[1], "\n", 1);
	free(str);
	return (0);
}

void	ft_hdoc_sig(char *limitor)
{
	write(2, "minishell: warning: here-document", 33);
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, limitor, ft_strlen(limitor));
	write(2, "\')\n", 3);
}

void	ft_ambig(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ambiguous redirect\n", 21);
}
