/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:12:35 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:13:19 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_dir(char **args, t_env *env)
{
	t_env	*the_env;

	if (args[1] == NULL)
	{
		the_env = ft_find_in_env(env, "HOME=", 5);
		if (!the_env)
			return (write(2, "minishell: cd: HOME not set\n", 28), 1);
		if (chdir(the_env->line + 5) == -1)
			return (write(2, "minishell: cd: ", 15), perror(args[1]), 1);
		return (0);
	}
	if (ft_strncmp("-", args[1], ft_strlen(args[1])) == 0)
	{
		the_env = ft_find_in_env(env, "OLDPWD=", 7);
		if (!the_env)
			return (write(2, "minishell: cd: OLDPWD not set\n", 30), 1);
		if (chdir(the_env->line + 7) == -1)
			return (write(2, "minishell: cd: ", 15), perror(args[1]), 1);
		return (0);
	}
	if (chdir(args[1]) == -1)
		return (write(2, "minishell: cd: ", 15), perror(args[1]), 1);
	return (0);
}

int	ft_cd_realloc_msh_env(t_env *env, char *old_pwd, char *pwd)
{
	t_env	*the_env;

	the_env = ft_find_in_env(env, "OLDPWD=", 7);
	if (the_env != NULL)
	{
		free(the_env->line);
		the_env->line = old_pwd;
	}
	else
	{
		if (ft_add_to_msh_env(env, old_pwd))
			return (1);
	}
	the_env = ft_find_in_env(env, "PWD=", 4);
	if (the_env != NULL)
	{
		free(the_env->line);
		the_env->line = pwd;
		return (0);
	}
	return (ft_add_to_msh_env(env, pwd));
}

int	ft_cd_update_msh_env(t_env *env, char *start_dir, char *end_dir)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = ft_strjoin("OLDPWD=", start_dir);
	if (!old_pwd)
	{
		ft_error(NULL, 0, 1);
		return (free(start_dir), free(end_dir), 1);
	}
	free(start_dir);
	pwd = ft_strjoin("PWD=", end_dir);
	if (!pwd)
	{
		ft_error(NULL, 0, 1);
		return (free(old_pwd), free(end_dir), 1);
	}
	free(end_dir);
	return (ft_cd_realloc_msh_env(env, old_pwd, pwd));
}

int	ft_cd(char **args, t_env *env, int fd)
{
	char	*start_dir;
	char	*end_dir;

	if (args[1] != NULL && args[2] != NULL)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (args[1] != NULL && (ft_strlen(args[1]) > 255))
	{
		write(2, "minishell: cd: ", 15);
		write(2, args[1], ft_strlen(args[1]));
		return (write(2, ": File name too long\n", 21), 1);
	}
	start_dir = getcwd(NULL, 0);
	if (!start_dir)
		return (ft_error("cd", 0, 1));
	if (ft_change_dir(args, env))
		return (free(start_dir), 1);
	end_dir = getcwd(NULL, 0);
	if (!end_dir)
		return (ft_error("cd", 0, 1), free(start_dir), 1);
	if (args[1] != NULL && ft_strncmp("-", args[1], ft_strlen(args[1])) == 0)
	{
		write(fd, end_dir, ft_strlen(end_dir));
		write(fd, "\n", 1);
	}
	return (ft_cd_update_msh_env(env, start_dir, end_dir));
}
