#include "../../inc/minishell.h"

int	is_built(char *str)
{
	int		i;
	char	*tab[7];

	i = 0;
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

int	ft_do_builtin(t_group *group, t_list_env *env, int out_fd)
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
		return (ft_exit(group));
	if (out_fd != 1)				// ???
	{
		close(out_fd);
		out_fd = 1;
	}
	return (0);
}
