#include "../../inc/minishell.h"

void	ft_write_export(t_list_env *env, int fd)
{
    char **envp;
    int i;

    envp = get_envp(env);
    if (!envp)
        return ;
    i = 0;
    while (envp[i] != NULL)
    {
        ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(envp[i], fd);
		ft_putstr_fd("\n", fd);
        i++;
    }
	free_tab(envp);
}

int	ft_export_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_err("minishell: export: `");
		ft_putstr_err(str);
		ft_putstr_err("\': not a valid identifier\n");
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putstr_err( "minishell: export: `");
			ft_putstr_err(str);
			ft_putstr_err("\': not a valid identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

////

int	ft_export(t_group *group, t_list_env *env, int fd)
{
	int		i;
	int		error_flag;

	if (group->cmd[1] == NULL)
		return (ft_write_export(env, fd), 0);
	i = 1;
	error_flag = 0;
	while (group->cmd[i] != NULL)
	{
		if (ft_export_is_valid(group->cmd[i]))
		{
			if (ft_export_replace_or_add(env, group->cmd[i]))
				return (1);
		}
		else
			error_flag = 1;
		i++;
	}
	return (error_flag);
}