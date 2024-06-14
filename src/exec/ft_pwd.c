#include "minishell.h"

//нет проверки на наличие опций, ок ли это

//не нужно ли использовать это: cur_path = get_env_var("PWD", env_list); - вроде бы вызов pwd не зависит от переменных окружения

int	ft_pwd(int fd)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_error("pwd", 0, 1));
	write(fd, current_dir, ft_strlen(current_dir));
	write(fd, "\n", 1);
	free(current_dir);
	return (0);
}
