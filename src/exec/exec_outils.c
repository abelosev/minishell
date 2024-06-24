/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:13:32 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/24 20:12:53 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *name, int type, int code)
{
	if (type == 0)
	{
		if (name == NULL)
			perror("minishell");
		else
		{
			ft_putstr_err("minishell: ");
			perror(name);
		}
	}
	if (type == 1 && name)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(name);
		ft_putstr_err(": command not found\n");
	}
	return (code);
}

//need signals inside (except of heredoc)

int	get_hd_fd(t_main *p, t_list_env *env, int *code)
{
	int		fd_hd;
	char	*file_hd;

	if (p->hd_del == NULL)
		return (STDIN_FILENO);
	file_hd = heredoc(env, p->hd_del, code);
	if (!file_hd)
		return (STDIN_FILENO);
	fd_hd = open(file_hd, O_RDONLY);
	free(file_hd);
	if (fd_hd < 0)
		return (STDIN_FILENO);
	return (fd_hd);
}

void ft_wait2(t_exec *e, int *code)
{
	int i;

	i = 0;
	while(i < e->group_count)
	{
		if(e->cpid[i] != -1)
		{
			// signal(SIGINT, ft_sigint);
        	// signal(SIGQUIT, ft_sigquit);
			waitpid(e->cpid[i], code, 0);
			// if(e->cpid[i] == e->last_pid)
			// {
				// if (*code == SIGINT)
				// {
				// 	// ft_putstr_err( "\n");
				// 	*code = SIGINT + 128;
				// }
				// else if (*code == 131)
				// {
				// 	ft_putstr_err( "Quit (core dumped)\n");
				// 	// *code = 131;
				// }
			// }
		}
		i++;
	}
	// free(e->cpid);
}
