#include "../../inc/exec.h"

int	builtin_pwd(t_group *group)
{
	size_t	size;
	char	*buf;
	char	*dir;

	size = 0;
	buf = NULL;
	if (tab_size(group->cmd) > 1)
	{
		if (ft_strncmp(group->cmd[1], "-", 1) == 0 \
								&& !is_char(group->cmd[1], '-'))
			return (5);
	}
	else
	{
		dir = getcwd(buf, size);
		ft_putstr(dir);
		write(1, "\n", 1);
		free(buf);
		free(dir);
		return (0);
	}
	free(buf);
	return (4);
}
