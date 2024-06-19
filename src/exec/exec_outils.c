/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:13:32 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:49:19 by abelosev         ###   ########.fr       */
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

void	ft_wait(int num_pipes, int (*pipes)[2], int *code)
{
    int		status;
    pid_t	pid;
    int		i;

    while ((pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status)) {
            *code = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            *code = WTERMSIG(status) + 128;
            if (WTERMSIG(status) == SIGINT) {
                write(STDERR_FILENO, "\n", 1);
            } else if (WTERMSIG(status) == SIGQUIT) {
                write(STDERR_FILENO, "Quit (core dumped)\n", 19);
            }
        } else {
            *code = 1;
        }
    }
    i = 0;
    while(i < num_pipes)
	{
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}
