#include "../../inc/minishell.h"

void    sig_quit(int sig)
{
    (void)sig;
    status = 131;
    ft_putstr_err("Quit (core dumped)\n");
    return ;
}

void    sig_int(int sig)
{
    (void)sig;
    status = 130;
    ft_putstr_err("^C\n"); //проверить, не просто ли \n
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    parent_sigint(int sig)
{
    (void)sig;
    status = 130;
    ft_putstr_err("^C\n"); //проверить, не просто ли \n
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_done = 1;
}

void    parent_sig(void)
{
    rl_event_hook = 0;
    signal(SIGINT, &parent_sigint);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}
