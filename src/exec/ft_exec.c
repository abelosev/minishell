/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:07 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/16 19:49:33 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipes {
    int **pipe;     // Массив для хранения дескрипторов каналов
    int pipe_nmbs;  // Общее количество каналов
} t_pipes;


int count_groups(t_main *p) {
    int count = 0;
    t_group *curr = p->group;

    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    return count;
}

void assign_group_ids(t_main *p) {
    int id = 1;
    t_group *curr = p->group;

    while (curr != NULL) {
        curr->id = id++;
        curr = curr->next;
    }
}


int is_redir(t_group *group) {
    return (group->redir_in || group->redir_out || group->app_out);
}

int open_redir(t_group *group, int *fd_in, int *fd_out) {
    if (group->redir_in) {
        *fd_in = open(group->redir_in, O_RDONLY);
        if (*fd_in < 0)
            return 1;
    }
    if (group->app_out) {
        *fd_out = open(group->app_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (*fd_out < 0)
            return 1;
    } else if (group->redir_out) {
        *fd_out = open(group->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (*fd_out < 0)
            return 1;
    }
    return 0;
}

void wait_for_children(int *code)
{
    int status;
    pid_t pid;

    while ((pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
            *code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
        {
            *code = WTERMSIG(status) + 128;
            if (WTERMSIG(status) == SIGINT)
                write(STDERR_FILENO, "\n", 1);
            else if (WTERMSIG(status) == SIGQUIT)
                write(STDERR_FILENO, "Quit (core dumped)\n", 19);
        }
        else
            *code = 1;
    }
}

// Функция для инициализации каналов
t_pipes *init_pipes(int num_groups) {
    t_pipes *pipex = malloc(sizeof(t_pipes));
    if (!pipex) {
        perror("malloc failed");
        return NULL;
    }

    pipex->pipe_nmbs = 2 * (num_groups - 1); // Вычисляем общее количество каналов

    // Выделяем память под массив каналов
    pipex->pipe = malloc(sizeof(int *) * pipex->pipe_nmbs);
    if (!pipex->pipe) {
        perror("malloc failed");
        free(pipex);
        return NULL;
    }

    // Создаем каждый канал
    for (int i = 0; i < pipex->pipe_nmbs; i++) {
        pipex->pipe[i] = malloc(sizeof(int) * 2);
        if (pipe(pipex->pipe[i]) == -1) {
            perror("pipe failed");
            // Освобождаем ресурсы и выходим
            for (int j = 0; j < i; j++) {
                close(pipex->pipe[j][0]);
                close(pipex->pipe[j][1]);
                free(pipex->pipe[j]);
            }
            free(pipex->pipe);
            free(pipex);
            return NULL;
        }
    }

    return pipex;
}

// Функция для освобождения ресурсов каналов
void parent_free(t_pipes *pipex) {
    if (!pipex) return;

    // Закрываем все открытые дескрипторы каналов
    for (int i = 0; i < pipex->pipe_nmbs; i++) {
        close(pipex->pipe[i][0]);
        close(pipex->pipe[i][1]);
        free(pipex->pipe[i]);
    }

    // Освобождаем массив каналов и структуру t_pipes
    free(pipex->pipe);
    free(pipex);
}

// Функция для выполнения встроенной команды
void exec_builtin(t_group *group, t_list_env *env, t_main *p, int fd_out, int *code) {
    *code = ft_do_builtin(group, env, fd_out, code);
    if (is_built(group->cmd[0]) == B_EXIT) {
        ft_putstr_err("exit\n");
        free_envp_list(env);
        if (p)
            free_main(p);
        clear_history();
        exit(*code);
    }
}



// Функция ft_cmd_parent (предположим, что она создана для работы с родительским процессом)
void ft_cmd_parent(int fd_in, int fd_out, t_pipes *pipex) {
    close(pipex->pipe[fd_in][0]); // Закрываем неиспользуемый конец канала
    dup2(pipex->pipe[fd_out][1], STDOUT_FILENO); // Перенаправляем вывод на следующий процесс
    close(pipex->pipe[fd_out][1]); // Закрываем используемый конец канала
}

// Функция ft_cmd_child (предположим, что она создана для работы с дочерним процессом)
void ft_cmd_child(t_group *group, t_list_env *env, int fd_in, int fd_out, t_pipes *pipex) {
    char **new_envp = get_envp(env);
    if (!new_envp) {
        perror("get_envp failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Дочерний процесс

        // Закрываем неиспользуемые дескрипторы каналов
        for (int i = 0; i < pipex->pipe_nmbs; i++) {
            close(pipex->pipe[i][0]);
            close(pipex->pipe[i][1]);
        }

        // Устанавливаем ввод и вывод для текущей команды
        if (fd_in != STDIN_FILENO) {
            dup2(pipex->pipe[fd_in][0], STDIN_FILENO);
            close(pipex->pipe[fd_in][0]);
        }
        if (fd_out != STDOUT_FILENO) {
            dup2(pipex->pipe[fd_out][1], STDOUT_FILENO);
            close(pipex->pipe[fd_out][1]);
        }

        // Выполняем команду
        execve(group->cmd[0], group->cmd, new_envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    // Освобождаем память
    free_tab(new_envp);
}

void execute_commands(t_main *p, t_list_env *env) {
    t_group *curr = p->group;
    int num_groups = count_groups(p);
    t_pipes *pipex = init_pipes(num_groups);
    int code = 0;
    int fd_in = STDIN_FILENO;
    int fd_out = STDOUT_FILENO;

    if (!pipex) {
        perror("Failed to initialize pipes");
        return;
    }

    // Присваиваем уникальные id группам
    assign_group_ids(p);

    while (curr) {
        if (curr->next) {
            fd_out = pipex->pipe[curr->id - 1][1];
        } else {
            fd_out = STDOUT_FILENO;
        }

        if (is_redir(curr)) {
            if (open_redir(curr, &fd_in, &fd_out) || fd_out < 0) {
                perror("open output failed");
                parent_free(pipex);
                return;
            }
        }

        if (is_built(curr->cmd[0]) != 0) {
            if (curr->next)
                exec_builtin(curr, env, p, fd_out, &code);
            else
                exec_builtin(curr, env, p, STDOUT_FILENO, &code);
        } else {
            if (curr->next)
                ft_cmd_child(curr, env, fd_in, fd_out, pipex);
            else
                ft_cmd_child(curr, env, fd_in, STDOUT_FILENO, pipex);
        }

        if (curr->next) {
            fd_in = pipex->pipe[curr->id][0];
        } else {
            fd_in = STDIN_FILENO;
        }

        curr = curr->next;
    }

    parent_free(pipex);
}
   
     
// Функция для выполнения всех команд с ожиданием завершения
void ft_exec(t_main *p, t_list_env *env, int *code) {
    execute_commands(p, env);
    wait_for_children(code);
    if (p)
        free_main(p);
}












// int is_redir(t_group *group)
// {
//     return (group->redir_in || group->redir_out || group->app_out);
// }

// int open_redir(t_group *group, int *fd_in, int *fd_out)
// {
//     if (group->redir_in)
//     {
//         *fd_in = open(group->redir_in, O_RDONLY);
//         if (*fd_in < 0)
//             return 1;
//     }
//     if (group->app_out)
//     {
//         *fd_out = open(group->app_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         if (*fd_out < 0)
//             return 1;
//     }
//     else if (group->redir_out)
//     {
//         *fd_out = open(group->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (*fd_out < 0)
//             return 1;
//     }
//     return 0;
// }

// void exec_builtin(t_group *group, t_list_env *env, t_main *p, int fd_out, int *code)
// {
//     *code = ft_do_builtin(group, env, fd_out, code);
//     if (is_built(group->cmd[0]) == B_EXIT)
//     {
//         ft_putstr_err("exit\n");
//         free_envp_list(env);
//         if (p)
//             free_main(p);
//         clear_history();
//         exit(*code);
//     }
// }

// void ft_cmd(t_group *group, t_list_env *env, int fd_in, int fd_out, int *code)
// {
//     pid_t pid;
//     char **new_envp;
	
// 	new_envp = get_envp(env);
//     if (!new_envp)
//     {
//         *code = 1;
//         return;
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         if (fd_in != STDIN_FILENO)
//         {
//             dup2(fd_in, STDIN_FILENO);
//             close(fd_in);
//         }
//         if (fd_out != STDOUT_FILENO)
//         {
//             dup2(fd_out, STDOUT_FILENO);
//             close(fd_out);
//         }
//         execve(group->cmd[0], group->cmd, new_envp);
//         return(1);
//     }
//     else if (pid > 0)
//     {
//         if (fd_in != STDIN_FILENO)
//             close(fd_in);
//         if (fd_out != STDOUT_FILENO)
//             close(fd_out);
//     }
//     else
//         *code = 1;
//     free_tab(new_envp);
// }


// void wait_for_children(int *code)
// {
//     int status;
//     pid_t pid;

//     while ((pid = wait(&status)) > 0)
//     {
//         if (WIFEXITED(status))
//             *code = WEXITSTATUS(status);
//         else if (WIFSIGNALED(status))
//         {
//             *code = WTERMSIG(status) + 128;
//             if (WTERMSIG(status) == SIGINT)
//                 write(STDERR_FILENO, "\n", 1);
//             else if (WTERMSIG(status) == SIGQUIT)
//                 write(STDERR_FILENO, "Quit (core dumped)\n", 19);
//         }
//         else
//             *code = 1;
//     }
// }


// void execute_commands(t_main *p, t_list_env *env)
// {
//     t_group *curr = p->group;
//     int fd_in = STDIN_FILENO;
//     int fd_out = STDOUT_FILENO;
//     int pipefd[2];
//     int pipe_res;
//     int code = 0;

//     while (curr)
//     {
//         if (curr->next)
//         {
//             pipe_res = pipe(pipefd);
//             if (pipe_res == -1)
//             {
//                 perror("pipe failed");
//                 return;
//             }
//             fd_out = pipefd[1];
//         }
//         else
//         {
//             fd_out = STDOUT_FILENO;
//         }
//         if (is_redir(curr))
//         {
//             if (open_redir(curr, &fd_in, &fd_out) || fd_out < 0)
//             {
//                 perror("open output failed");
//                 return;
//             }
//         }
//         if (is_built(curr->cmd[0]) != 0)
//         {
//             if (curr->next)
//                 exec_builtin(curr, env, p, fd_out, &code);
//             else
//                 exec_builtin(curr, env, p, STDOUT_FILENO, &code);
//         }
//         else
//         {
//             if (curr->next)
//                 ft_cmd(curr, env, fd_in, fd_out, &code);
//             else
//                 ft_cmd(curr, env, fd_in, STDOUT_FILENO, &code);
//         }
//         if (curr->next)
//         {
//             close(pipefd[1]);
//             fd_in = pipefd[0];
//         }

//         curr = curr->next;
//     }
//     if (fd_in != STDIN_FILENO)
//         close(fd_in);
//     if (fd_out != STDOUT_FILENO && pipe_res != 0)
//         close(fd_out);
// }


// void ft_exec(t_main *p, t_list_env *env, int *code)
// {
//     execute_commands(p, env);
//     wait_for_children(code);
//     if (p)
//         free_main(p);
// }


















// void	ft_exec(t_main *p, t_list_env *env, int *code)
// {
//     t_group *curr;
//     int fd_in;
// 	int file_fd;
// 	int fd_out;
//     int pipefd[2];
// 	char buffer[4096];		//можно ли так делать?
//     ssize_t bytes_read;
//     // int e_status;
//     int pipe_res;

// 	fd_in = get_hd_fd(p, env, code);	// передавать ли fd_in параметром (?)
//     curr = p->group;
//     pipe_res = 0;
//     while (curr)
//     {
//         if (curr->next)
//         {
// 			pipe_res = pipe(pipefd);
//             if (pipe_res == -1)
//             {
//                 if(p)
//                     free_main(p);
//                 ft_putstr_err("pipe failed");
//                 *code = 1;
//                 return ; // не удалось открыть пайп   
//             }
//         }

//         if (curr->flag_fail == 0 && curr->cmd && *(curr->cmd))
//         {
//             if (is_redir(curr))
//             {
//                 if(open_redir(curr, &fd_in, &fd_out) || fd_out < 0)
//                 {
//                     if(p)
//                         free_main(p);
//                     ft_putstr_err("open output failed");
//                     *code = 1;
//                     return ;
//                 }
                    
//                 do_redir(curr, p, env, fd_in, fd_out, code);
//                 close(fd_out);
//                 if (curr->next)
//                 {
//                     file_fd = open(curr->redir_out, O_RDONLY);
//                     if (file_fd < 0)
//                     {
//                         if(p)
//                             free_main(p);
//                         ft_putstr_err("open output file failed");
//                         *code = 1;
//                         return ;
//                     }
//                     while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0)
//                         write(pipefd[1], buffer, bytes_read);
//                     close(file_fd);
//                     close(pipefd[1]);
//                     fd_in = pipefd[0];
//                 }
//             }
//             else
//             {
//                 if (is_built(curr->cmd[0]) != 0)
// 				{
// 					if (curr->next)
// 						exec_builtin(curr, env, p, pipefd[1], code);
// 					else
// 						exec_builtin(curr, env, p, STDOUT_FILENO, code);
// 				}
//                 else
//                 {
// 					if (curr->next)
//     					ft_cmd(curr, env, fd_in, pipefd[1], code);
// 					else
//     					ft_cmd(curr, env, fd_in, STDOUT_FILENO, code);
// 				}
// 			}
//         }
//         else
//             *code = curr->flag_fail;

//         if (fd_in != STDIN_FILENO)
//             close(fd_in);
//         if (pipe_res != 0 && pipefd[1] != STDOUT_FILENO)
//             close(pipefd[1]);
// 		if (curr->next)
//             fd_in = pipefd[0];
//         curr = curr->next;
//     }
//     if (fd_in != STDIN_FILENO)
//         close(fd_in);
//     if(p)
//         free_main(p);
//     // return (status);
// }

