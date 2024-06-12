/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:22:27 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:25:54 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_arr(char **env_arr)
{
	int	i;

	i = 0;
	if (!env_arr || !env_arr[i])
		return ;
	while (env_arr[i])
	{
		if (env_arr[i])
			free(env_arr[i]);
		i++;
	}
	if (env_arr)
		free(env_arr);
}

int	ft_path_err(char **args)
{
	struct stat	buf;

	if (stat(args[0], &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": Is a directory\n", 17);
		ft_free_char_vector(args);
		return (126);
	}
	if (args)
		ft_free_char_vector(args);
	return (127);
}

int	ft_wait(pid_t *pids, int cmd_amnt, t_cmd **cmd_list)
{
	int	i;
	int	status;

	i = 0;
	ft_close_all(cmd_list);
	while (i < cmd_amnt)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return ((WTERMSIG(status) + 128));
}

int	ft_child(t_cmd **cmd_list, int i, t_env *env, int single_flag)
{
	int		exit_status;
	char	**args;
	char	*path;
	char	**env_arr;

	exit_status = ft_set_io(cmd_list, i, single_flag);
	if (exit_status)
		return (exit_status);
	if (!ft_get_arg_amnt(cmd_list[i]->tokens))
		return (0);
	args = ft_make_args(cmd_list[i]->tokens);
	if (!args)
		return (1);
	if (single_flag || ft_is_buildin(cmd_list[i]->tokens))
		return (ft_do_buildin(args, env, cmd_list, i));
	path = ft_find_cmd_path(args[0], env);
	if (!path)
		return (ft_path_err(args));
	env_arr = create_env_arr(env);
	execve(path, args, env_arr);
	ft_error(args[1], 0, 1);
	free(path);
	return (ft_free_char_vector(args), ft_free_char_vector(env_arr), 1);
}

int	ft_pipeline(t_cmd **cmd_list, int cmd_amnt, t_env *env, t_mini *msh)
{
	pid_t	*pids;
	int		i;
	int		exit_status;

	pids = malloc(sizeof(pid_t) * cmd_amnt);
	if (pids == NULL)
		return (ft_error(NULL, 0, 1));
	signal(SIGQUIT, &sigquit_handler);
	i = 0;
	while (i < cmd_amnt)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_error(NULL, 0, 1), ft_wait(pids, (i - 1), cmd_list));
		if (pids[i] == 0)
		{
			free(pids);
			exit_status = ft_child(cmd_list, i, env, 0);
			ft_close_all(cmd_list);
			ft_exec_msh_free(msh);
			exit (exit_status);
		}
		i++;
	}
	return (ft_wait(pids, i, cmd_list));
}
