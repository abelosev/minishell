#include "../../inc/minishell.h"

int	ft_error(char *name, int type, int exit_code)
{
	if (type == 0)
	{
		if (name == NULL)
			perror("minishell");
		else
		{
			write(2, "minishell: ", 11);
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