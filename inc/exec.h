#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

//TODO:
//redir struct
//buuiltin struct
//define error messages + code (exit exec->status)
//check flag fail, if 1 = fail

////////////////// BUILT_INS //////////////////
int			builtin_echo(t_group *group);
int			builtin_pwd(t_group *group);
int			builtin_cd(t_group *group, char *path, t_list_env *env_lst);
int			builtin_env(t_group *group, t_list_env *env_lst);
// void		builtin_exit(t_exec *exec, t_group *group, t_list_env *env_lst);
int			builtin_export(t_group *group, t_list_env *env_lst);
int			builtin_unset(t_group *group, t_list_env *env_lst);

////////////////// EXEC //////////////////
int			ft_builtins(t_exec *exec, t_group *group, t_list_env *env_lst);
int			ft_bin(t_exec *exec, t_group *group, t_list_env *env_lst);
// void		simple_cmd(t_exec *exec, t_group *group, t_list_env *env_lst);
// void		ft_redir(t_exec *exec, t_group *group);
// void		minish(t_exec *exec, t_group *group, t_list_env *env_lst);

////////////////// REDIRECTION //////////////////
void		redir_in(t_exec *exec, t_group *group);
void		redir_out(t_exec *exec, t_group *group);
void		append_out(t_exec *exec, t_group *group);

////////////////// SIGNALS //////////////////

////////////////// CHECKS //////////////////


////////////////// UTILS //////////////////

//built_ins
char		*set_path(t_list_env *env_lst, char *key);
int			is_built2(char *str);

// t_list_env	*env_lst_sos(void);
t_list_env	*check_var(t_list_env **env_lst, char *var);
void		mod_var(t_list_env **env_lst, char *var);
t_list_env	*remove_first(t_list_env **env_lst);
void		remove_var(t_list_env **env_lst);

//exec
// char		**split_cmds(char *line);
// void		init_std(t_exec *exec);
// void		reset_std(t_exec *exec);
// void		close_std(t_exec *exec);
// void		init_exec(t_exec *exec);
// void		close_fds(t_exec *exec);

//pipes
// void		ft_pipe(t_exec *exec);

//redirection
int			open_file(char *file, int std_no);

//signals

//libft
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr(char *str);
void		ft_putstr_fd(char *cmd, char *s, int fd);
int			is_char(char *str, char c);
int			is_empty(char *line);
int			tab_size(char **tab);
t_list_env	*ft_lstlast(t_list_env *lst);
void		ft_lstadd_back(t_list_env **lst, t_list_env *new);
int			group_size(t_group *group);

#endif