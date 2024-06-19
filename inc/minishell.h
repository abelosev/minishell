/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:12:38 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 20:15:11 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include "../libft/libft.h"

# define B_ECHO 1
# define B_CD 2
# define B_PWD 3
# define B_EXPORT 4
# define B_UNSET 5
# define B_ENV 6
# define B_EXIT 7

extern unsigned int	g_status;

////////////////// STRUCTS //////////////////

typedef struct s_group
{
	unsigned int	flag_fail;
	char			**cmd;
	char			*redir_in;
	char			*redir_out;
	char			*app_out;
	int				id;
	struct s_group	*next;
}	t_group;

typedef struct s_list_env
{
	char				*key;
	char				*value;
	struct s_list_env	*next;
}	t_list_env;

typedef struct s_main
{
	char	*hd_del;
	int		redir_fd[2];
	int		pipe_fd[3];
	// int		*code;
	t_group	*group;
}	t_main;

////////////////// FONCTIONS //////////////////

//input and parsing
int				only_spaces(char *str);
t_main			*parser(char *input, t_list_env *env, int *code);

//envp
char			**get_envp(t_list_env *list);
char			*get_value(char *str);
char			*get_key(char *str);
char			*get_value_by_key(t_list_env *env, char *target);
t_list_env		*get_mini_env(void);
t_list_env		*get_list(char **tab);
t_list_env		*ft_find_in_env(t_list_env *env, char *target_key);
t_list_env		*ft_new_env_node(char *key, char *value);
t_list_env		*change_shlvl(t_list_env *env);
int				ft_export_replace_or_add(t_list_env **env, char *str);
int				ft_add_to_msh_env(t_list_env **env, char *new_str);

//builtins
int				is_built(char *str);
int				ft_do_builtin(t_group *group, t_list_env *env, int out_fd, int *code);
int				ft_cd(t_group *group, t_list_env *env, int fd);
int				ft_echo(t_group *group, int fd);
int				ft_env(t_group *group, t_list_env *env, int fd);
int				ft_exit(t_group *group, int *code);
int				ft_export(t_group *group, t_list_env *env, int fd);
int				ft_pwd(int fd);
int				ft_unset(t_group *group, t_list_env **env);

//exec
void			ft_exec(t_main *p, t_list_env *env, int *code);
int				is_redir(t_group *group);
int				open_redir(t_group *group, int *fd_in, int *fd_out);
void			do_redir(t_group *group, t_main *p, t_list_env *env, int fd_in, int fd_out, int *code);
int				group_nb(t_group *group);
void			ft_wait(int num_pipes, int (*pipes)[2], int *code);
void			exec_builtin(t_group *group, t_list_env *env, t_main *p, int fd_out, int *code);
void			ft_cmd(t_group *group, t_list_env *env, int fd_in, int fd_out, int *code);
void			create_pipes(int num_pipes, int (*pipes)[2]);

//main_outils
int				check_group(t_main *parsed, char *line, int *code);
int				check_line(char *line, int *code);
char			*get_line(char *prompt);
t_list_env		*get_mini_env(void);
t_list_env		*change_shlvl(t_list_env *env);

//heredoc
char			*uniq_name(char *prefix);
char			*heredoc(t_list_env *env, char *del, int *code);
int				get_hd_fd(t_main *p, t_list_env *env, int *code);

//signals
void			ft_sigint(int signal);
void			ft_sigint_hd(int signal);

//free
void			free_tab(char **tab);
void			free_envp_list(t_list_env *list);
void			free_group_list(t_group *group);
void			free_main(t_main *parsed);

//outils
void			print_env_list(t_list_env *list, int fd);
void			print_tab(char **tab, int fd);
void			ft_putstr_err(char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_error(char *name, int type, int exit_code);

#endif