/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:20:41 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 10:19:14 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_pipes(t_cmd **cmd_list, int nbr_cmd)
{
	int	i;
	int	pipe_ends[2];

	i = 0;
	while (i < (nbr_cmd - 1))
	{
		if (pipe(pipe_ends) == -1)
			return (ft_error(NULL, 0, 1));
		cmd_list[i + 1]->in_fd = pipe_ends[0];
		cmd_list[i]->out_fd = pipe_ends[1];
		i++;
	}
	return (0);
}

int	ft_exec_init(t_cmd **cmd_list, int old_exit)
{
	int		i;
	t_token	*t;

	i = 0;
	while (cmd_list[i] != NULL)
	{
		cmd_list[i]->in_fd = 0;
		cmd_list[i]->out_fd = 1;
		cmd_list[i]->old_exit = old_exit;
		t = cmd_list[i]->tokens;
		while (t)
		{
			t->fd = 0;
			t = t->next;
		}
		i++;
	}
	return (i);
}

void	ft_exec_msh_free(t_mini *msh)
{
	if (!msh)
		return ;
	ft_free_all(msh->cmd_table, msh->env);
}

int	ft_exec(t_cmd **cmd_list, t_env *env, int e, t_mini *msh)
{
	int		exit_status;
	int		nbr_cmd;
	int		buildin_num;

	nbr_cmd = ft_exec_init(cmd_list, e);
	if (ft_set_hdoc(cmd_list, e, env) || ft_set_pipes(cmd_list, nbr_cmd))
	{
		ft_close_all(cmd_list);
		if (g_signal)
			return (ft_free_all(cmd_list, NULL), g_signal + 128);
		return (ft_free_all(cmd_list, NULL), 1);
	}
	buildin_num = ft_is_buildin(cmd_list[0]->tokens);
	if (nbr_cmd == 1 && buildin_num)
	{
		exit_status = ft_child(cmd_list, 0, env, 1);
		if (buildin_num == B_EXIT)
		{
			ft_exec_msh_free(msh);
			exit (exit_status);
		}
	}
	else
		exit_status = ft_pipeline(cmd_list, nbr_cmd, env, msh);
	return (ft_free_all(cmd_list, NULL), exit_status);
}
