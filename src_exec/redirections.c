/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:56 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 18:43:21 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

// Function to handle input redirection
void redir_in(t_exec *exec, t_group *group)
{
    if (exec->fd_in > 0)
        close(exec->fd_in);
    exec->fd_in = open(group->redir_in, O_RDONLY);
    if (exec->fd_in == -1)
    {
        perror("Error opening input redirection file");
        exit(EXIT_FAILURE);
    }
    dup2(exec->fd_in, STDIN_FILENO);
    close(exec->fd_in);
    exec->fd_in = STDIN_FILENO;
}

// Function to handle output redirection
void redir_out(t_exec *exec, t_group *group)
{
    if (exec->fd_out > 0 && exec->fd_out != STDOUT_FILENO)
        close(exec->fd_out);
    exec->fd_out = open(group->redir_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (exec->fd_out == -1)
    {
        perror("Error opening output redirection file");
        exit(EXIT_FAILURE);
    }
    dup2(exec->fd_out, STDOUT_FILENO);
    close(exec->fd_out);
    exec->fd_out = STDOUT_FILENO;
}

// Function to handle append output redirection
void append_out(t_exec *exec, t_group *group)
{
    if (exec->fd_out > 0 && exec->fd_out != STDOUT_FILENO)
        close(exec->fd_out);
    exec->fd_out = open(group->app_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (exec->fd_out == -1)
    {
        perror("Error opening append redirection file");
        exit(EXIT_FAILURE);
    }
    dup2(exec->fd_out, STDOUT_FILENO);
    close(exec->fd_out);
    exec->fd_out = STDOUT_FILENO;
}

// Function to handle redirections based on the group settings
void ft_redir(t_exec *exec, t_group *group)
{
    if (group->redir_in != NULL)
        redir_in(exec, group);
    if (group->redir_out != NULL)
        redir_out(exec, group);
    if (group->app_out != NULL)
        append_out(exec, group);
}
