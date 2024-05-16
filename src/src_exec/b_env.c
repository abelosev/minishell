#include "../../inc/exec.h"

int	builtin_env(t_group *group, t_list_env *env_lst)
{
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strcmp(group->cmd[1], "env") != 0)
			return (2);
	}
	if (ft_strncmp(group->cmd[0], "env", 3) == 0)
	{
		print_list(env_lst);
		return (0);
	}
	return (4);
}
