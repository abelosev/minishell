#include "../../inc/exec.h"

//voir pour le prmier node
//okay dans la fonction mais modifeir **env_lst pour aller au next

int	builtin_unset(t_group *group, t_list_env *env_lst)
{
	int	i;
	t_list_env	*tmp;

	i = 1;
	tmp = env_lst;
	if (tab_size(group->cmd) == 1)
		return (0);
	while (group->cmd[i])
	{
		if (ft_strncmp(env_lst->key, get_key(group->cmd[i]), \
										ft_strlen(group->cmd[i])) != 0)
		{
			env_lst = check_var(&env_lst, group->cmd[i]);
			remove_var(&env_lst);
		}
		else
		{
			remove_first(&env_lst);
			tmp = env_lst;
		}
		env_lst = tmp;
		i++;
	}
	return (0);
}
