#include "minishell.h"

int	ft_error(char *name, int type, int exit_code)
{
	if (type == 0)
	{
		if (name == NULL)
			perror("minishell");
		else
		{
			ft_putstr_err("minishell: ");
			perror(name);
		}
	}
	if (type == 1 && name)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(name);
		ft_putstr_err(": command not found\n");
	}
	return (exit_code);
}

//need signals inside (except of heredoc)

int	get_hd_fd(t_parsed *p, t_list_env *env)
{
	int fd_hd;
	char *file_hd;

	if(p->hd_del == NULL)
		return (STDIN_FILENO);
	file_hd = heredoc(env, p->hd_del);
	if(!file_hd)
		return (STDIN_FILENO);
	fd_hd = open(file_hd, O_RDONLY);
	free(file_hd);
	if(fd_hd < 0)
		return (STDIN_FILENO);
	return (fd_hd);
}
