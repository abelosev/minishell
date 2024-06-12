/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:11:31 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:11:39 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_buildin_num(char	*cmd_name)
{
	int	buildin_num;
	int	len;

	len = ft_strlen(cmd_name);
	if (len == 4 && ft_strncmp(cmd_name, "echo", len) == 0)
		buildin_num = B_ECHO;
	else if (len == 2 && ft_strncmp(cmd_name, "cd", len) == 0)
		buildin_num = B_CD;
	else if (len == 3 && ft_strncmp(cmd_name, "pwd", len) == 0)
		buildin_num = B_PWD;
	else if (len == 6 && ft_strncmp(cmd_name, "export", len) == 0)
		buildin_num = B_EXPORT;
	else if (len == 5 && ft_strncmp(cmd_name, "unset", len) == 0)
		buildin_num = B_UNSET;
	else if (len == 3 && ft_strncmp(cmd_name, "env", len) == 0)
		buildin_num = B_ENV;
	else if (len == 4 && ft_strncmp(cmd_name, "exit", len) == 0)
		buildin_num = B_EXIT;
	else
		buildin_num = 0;
	return (buildin_num);
}

int	ft_do_buildin(char **args, t_env *env, t_cmd **cmd_list, int i)
{
	int	buildin_num;
	int	exit_code;

	exit_code = 0;
	buildin_num = ft_get_buildin_num(args[0]);
	if (buildin_num == B_ECHO)
		exit_code = ft_echo(args, cmd_list[i]->out_fd);
	else if (buildin_num == B_CD)
		exit_code = ft_cd(args, env, cmd_list[i]->out_fd);
	else if (buildin_num == B_PWD)
		exit_code = ft_pwd(cmd_list[i]->out_fd);
	else if (buildin_num == B_EXPORT)
		exit_code = ft_export(args, env, cmd_list[i]->out_fd);
	else if (buildin_num == B_UNSET)
		exit_code = ft_unset(args, env);
	else if (buildin_num == B_ENV)
		exit_code = ft_env(args, env, cmd_list[i]->out_fd);
	else if (buildin_num == B_EXIT)
		exit_code = ft_exit(args, cmd_list, i);
	if (cmd_list[i]->out_fd != 1)
	{
		close(cmd_list[i]->out_fd);
		cmd_list[i]->out_fd = 1;
	}
	return (ft_free_char_vector(args), exit_code);
}

int	ft_is_buildin(t_token *tokens)
{
	t_token	*current_token;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->type == ARG)
			return (ft_get_buildin_num(current_token->word));
		current_token = current_token->next;
	}
	return (0);
}
