#include "../../inc/minishell.h"

void	ft_sigint(int signal)
{
	(void)signal;
	ft_putstr_err("^C\n"); //проверить, не просто ли \n
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_hd(int signal)
{
	(void)signal;
	close(STDIN_FILENO);
	ft_putstr_err("^C\n");
}
