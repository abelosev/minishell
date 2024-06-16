/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:12:38 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 18:11:44 by aauthier         ###   ########.fr       */
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

extern unsigned int	status;

////////////////// STRUCTS //////////////////

typedef struct s_group
{
	unsigned int	flag_fail;
	char			**cmd;
	char			*redir_in;
	char			*redir_out;
	char			*app_out;
	struct s_group	*next;
}	t_group;

typedef struct s_list_env
{
	char				*key;
	char				*value;
	struct s_list_env	*next;
}	t_list_env;

typedef struct s_parsed
{
	char	*hd_del;
	int		redir_fd[2];
	int		pipe_fd[3];
	t_group	*group;
}	t_parsed;

////////////////// FONCTIONS //////////////////

//input and parsing
int				only_spaces(char *str);
t_parsed		*parser(char *input, t_list_env *env);

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
int				ft_do_builtin(t_group *group, t_list_env *env, int out_fd);
int				ft_cd(t_group *group, t_list_env *env, int fd);
int				ft_echo(t_group *group, int fd);
int				ft_env(t_group *group, t_list_env *env, int fd);
int				ft_exit(t_group *group);
int				ft_export(t_group *group, t_list_env *env, int fd);
int				ft_pwd(int fd);
int				ft_unset(t_group *group, t_list_env **env);

//exec
unsigned int	ft_exec(t_parsed *p, t_list_env *env);

//main_outils
int				check_group(t_parsed *parsed, char *line);
int				check_line(char *line);
char			*get_line(char *prompt);
t_list_env		*get_mini_env(void);
t_list_env		*change_shlvl(t_list_env *env);

//heredoc
char			*uniq_name(char *prefix);
char			*heredoc(t_list_env *env, char *del);
int				get_hd_fd(t_parsed *p, t_list_env *env);

//signals
void			ft_sigint(int signal);
void			ft_sigint_hd(int signal);

//free
void			free_tab(char **tab);
void			free_envp_list(t_list_env *list);
void			free_group_list(t_group *group);
void			free_parsed(t_parsed *parsed);

//outils
void			print_env_list(t_list_env *list, int fd);
void			print_tab(char **tab, int fd);
void			ft_putstr_err(char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_error(char *name, int type, int exit_code);
int				ft_strcmp(const char *s1, const char *s2);

#endif
