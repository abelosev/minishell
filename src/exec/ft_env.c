#include "../../inc/minishell.h"

int ft_env(t_group *group, t_list_env *env, int fd)
{
	if (group->cmd[1] != NULL && ft_strncmp(group->cmd[1], "env", ft_strlen(group->cmd[1]))) //проверить
	{
		ft_putstr_err("env : ");
		ft_putstr_err(group->cmd[1]);
		ft_putstr_err(": No such file or directory\n");
		return (127); //проверить, не 125 ли
	}
	print_list(env);
}