/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 03:12:12 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:40:26 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built(char *str)
{
	int		i;
	char	*tab[7];

	i = 0;
	if (!str)
		return (0);
	tab[0] = "echo";
	tab[1] = "cd";
	tab[2] = "pwd";
	tab[3] = "export";
	tab[4] = "unset";
	tab[5] = "env";
	tab[6] = "exit";
	while (i <= 6)
	{
		if (ft_strlen(tab[i]) == ft_strlen(str) && ft_strcmp(str, tab[i]) == 0)
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_do_builtin(t_group *group, t_list_env *env, int out_fd, int *code)
{
	int	built_num;

	built_num = is_built(group->cmd[0]);
	if (built_num == B_ECHO)
		return (ft_echo(group, out_fd));
	else if (built_num == B_CD)
		return (ft_cd(group, env, out_fd));
	else if (built_num == B_PWD)
		return (ft_pwd(out_fd));
	else if (built_num == B_EXPORT)
		return (ft_export(group, env, out_fd));
	else if (built_num == B_UNSET)
		return (ft_unset(group, &env));
	else if (built_num == B_ENV)
		return (ft_env(group, env, out_fd));
	else if (built_num == B_EXIT)
		return (ft_exit(group, code));
	if (out_fd != 1)
	{
		close(out_fd);
		out_fd = 1;
	}
	return (0);
}

void    exec_builtin(t_main *p, t_list_env *env, t_exec *e, int *code)
{
    t_group *group;

    group = p->group;
    *code = ft_do_builtin(group, env, e->fd_out, code);
    if (is_built(group->cmd[0]) == B_EXIT  && e->group_count == 1)	//???
	{
        ft_putstr_err("exit\n");
        free_envp_list(env);
        if (p)
            free_main(p);
        if (e->cpid)
            free(e->cpid);
        clear_history();
        exit(*code);
    }
}
