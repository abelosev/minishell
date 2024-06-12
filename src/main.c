/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:30 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/07 22:27:43 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

unsigned int	status;

int	is_exit(char *line)
{
	if(ft_strlen(line) != 4)
		return (1);
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		if(line)
			free(line);
		return (0);
	}
	else
		return (1);
}

unsigned int status = 0;

int main(int ac, char **av, char **envp)
{
    char *line;
    t_group *group;
    t_list_env *env;
    t_exec exec;
    t_group *start;

    int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);

    (void)ac;
    (void)av[0];
    if (*envp == NULL)
        env = env_lst_sos();
    else
    {
        // obtenir t_env_list envp + changer $SHLVL
        env = get_list(envp);
    }
    init_exec(&exec);

    while (1)
    {
        line = readline(">$ ");
        if (!line)
        {
            break;
        }

        if (is_exit(line) == 0)
        {
            free(line);
            break;
        }

        if (*line == '\0' || only_spaces(line) || ft_strncmp(line, ":", ft_strlen(line)) == 0 || ft_strncmp(line, "!", ft_strlen(line)) == 0)
        {
            free(line);
            continue;
        }

        if (line && *line)
            add_history(line);

        group = parser(line, env);
        if (!group)
        {
            status = 1; // ??
            free(line);
            continue;
        }

        start = group;
        minish(&exec, group, &env);
        free_group_list(start);
        reset_minish(&exec);

        dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);

        free(line);
    }

    free_envp_list(env);
    clear_history();
    close_fds(&exec);
    close(original_stdin);
    close(original_stdout);
    return (status);
}
