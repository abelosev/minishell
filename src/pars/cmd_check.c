/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:12:48 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/14 04:29:56 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

char	**get_path_tab(char **envp)
{
	char	**res;

	res = NULL;
	if (envp == NULL || *envp == NULL)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			res = ft_split1(*envp + 5, 2);
			if (res != NULL)
				return (res);
		}
		envp++;
	}
	return (NULL);
}

int	find_path(char **path_list, char **str)
{
	char	*prefix;
	char	*arg_w_path;
	int		i;

	i = 0;
	arg_w_path = NULL;
	while (path_list[i])
	{
		prefix = ft_strjoin(path_list[i], "/");
		arg_w_path = ft_strjoin(prefix, (*str));
		if (access(arg_w_path, F_OK | X_OK) == 0)
		{
			free(prefix);
			free(*str);
			*str = arg_w_path;
			return (1);
		}
		free(prefix);
		free(arg_w_path);
		i++;
	}
	return (0);
}

int	cmd_standart(char **str, t_list_env *env)
{
	char	**path_tab;
	char	**new_envp;
	int		code;
	int		path_check;

	path_tab = NULL;
	new_envp = get_envp(env);
	if (new_envp == NULL)
		return (1);
	path_tab = get_path_tab(new_envp);
	if (path_tab == NULL)
		return (1);
	path_check = find_path(path_tab, str);
	if (path_check == 0)
	{
		code = 127;
		ft_putstr_err(*str);
		ft_putstr_err(": Command not found\n");
	}
	else
		code = 0;
	free_tab(new_envp);
	free_tab(path_tab);
	return (code);
}

int	cmd_check(char **str, t_list_env *env)
{
	int		code;

	if (is_built(*str) != 0)
		code = 0;
	else if (is_folder(*str))
		code = 126;
	else if (!ft_strchr(*str, '/'))
		code = cmd_standart(str, env);
	else if (ft_strchr(*str, '/') && (access(*str, F_OK | X_OK | R_OK) == 0))
		code = 0;
	else
	{
		code = 127;
		ft_putstr_err(*str);
		ft_putstr_err(": Command not found\n");
	}
	return (code);
}
