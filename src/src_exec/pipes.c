/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:05:48 by memarign          #+#    #+#             */
/*   Updated: 2024/06/07 22:32:22 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	child_pid(t_exec *exec, int *pipe_fd)
{
    // Закрываем конец для записи, так как нам нужно только читать из пайпа
    close(pipe_fd[1]);
    // Дублируем pipe_fd[0] в STDIN_FILENO
    dup2(pipe_fd[0], STDIN_FILENO);
    // Закрываем оригинальный дескриптор pipe_fd[0] после дублирования
    close(pipe_fd[0]);
    // Обновляем pfd_in в структуре exec
    exec->pfd_in = pipe_fd[0];
}

void	parent_pid(t_exec *exec, int *pipe_fd)
{
    // Ожидаем завершения дочернего процесса
    waitpid(-1, NULL, 0);
    // Закрываем конец для чтения, так как нам нужно только писать в пайп
    close(pipe_fd[0]);
    // Дублируем pipe_fd[1] в STDOUT_FILENO
    dup2(pipe_fd[1], STDOUT_FILENO);
    // Закрываем оригинальный дескриптор pipe_fd[1] после дублирования
    close(pipe_fd[1]);
    // Обновляем pfd_out в структуре exec
    exec->pfd_out = pipe_fd[1];
}

void ft_pipe(t_exec *exec)
{
    pid_t pid;
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // Child process
        close(pipe_fd[1]); // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
        close(pipe_fd[0]); // Close read end of the pipe
        exec->pfd_in = STDIN_FILENO; // Update input file descriptor in the exec struct
        // Execute the command here, e.g., execlp(...)
    }
    else
    {
        // Parent process
        close(pipe_fd[0]); // Close read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to write end of the pipe
        close(pipe_fd[1]); // Close write end of the pipe
        exec->pfd_out = STDOUT_FILENO; // Update output file descriptor in the exec struct
        // Wait for the child process to finish
        waitpid(pid, NULL, 0);
    }
}
