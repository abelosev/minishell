#include "minishell.h"

int ft_change_dir(t_group *group, t_list_env *env)
{
    t_list_env *the_env;

    if (group->cmd[1] == NULL)
    {
        the_env = ft_find_in_env(env, "HOME");
        if (!the_env)
			return(ft_putstr_err("minishell: cd: HOME not set\n"), 1);
        if (chdir(the_env->value) == -1)
            return (ft_putstr_err("minishell: cd: "), perror(group->cmd[1]), 1);
        return (0);
    }
    if (ft_strcmp("-", group->cmd[1]) == 0)
    {
        the_env = ft_find_in_env(env, "OLDPWD");
        if (!the_env)
            return (ft_putstr_err("minishell: cd: OLDPWD not set\n"), 1);
        if (chdir(the_env->value) == -1)
            return (ft_putstr_err("minishell: cd: "), perror(group->cmd[1]), 1);
        return (0);
    }
    if (chdir(group->cmd[1]) == -1)
        return (ft_putstr_err("minishell: cd: "), perror(group->cmd[1]), 1);
    return (0);
}

int	ft_cd_realloc_msh_env(t_list_env **env, char *old_pwd, char *pwd)
{
	t_list_env	*the_env;

	the_env = ft_find_in_env(*env, "OLDPWD");
	if (the_env != NULL)
	{
		free(the_env->value);
		the_env->value = old_pwd;
	}
	else
	{
		if (ft_add_to_msh_env(env, old_pwd))
			return (1);
	}
	the_env = ft_find_in_env(*env, "PWD");
	if (the_env != NULL)
	{
		free(the_env->value);
		the_env->value = pwd;
		return (0);
	}
	return (ft_add_to_msh_env(env, pwd));
}

int	ft_cd_update_msh_env(t_list_env **env, char *start_dir, char *end_dir)
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

int	ft_cd(t_group *group, t_list_env *env, int fd)
{
	char	*start_dir;
	char	*end_dir;

	if (group->cmd[1] && group->cmd[2])
		return (ft_putstr_err("minishell: cd: too many arguments\n"), 1);
	if (group->cmd[1] && (ft_strlen(group->cmd[1]) > 255))
	{
		ft_putstr_err("minishell: cd: ");
		ft_putstr_err(group->cmd[1]);
		return(ft_putstr_err(": File name too long\n"), 1);
	}
	start_dir = getcwd(NULL, 0);
	if (!start_dir)
		return (ft_error("cd", 0, 1));
	if (ft_change_dir(group, env))
		return (free(start_dir), 1);
	end_dir = getcwd(NULL, 0);
	if (!end_dir)
		return (ft_error("cd", 0, 1), free(start_dir), 1);
	if (group->cmd[1] != NULL && ft_strcmp("-", group->cmd[1]) == 0)
	{
		write(fd, end_dir, ft_strlen(end_dir));
		write(fd, "\n", 1);
	}
	return (ft_cd_update_msh_env(&env, start_dir, end_dir));
}
