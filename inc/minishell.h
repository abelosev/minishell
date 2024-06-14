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
	unsigned int flag_fail;
	char **cmd;
	char *redir_in;
	char *redir_out;
	char *app_out;
	char *app_in;
	struct s_group *next;
} t_group;

typedef struct s_list_env
{
	char *key;
	char *value;
	struct s_list_env *next;
} t_list_env;

// typedef struct s_exec
// {
// 	int				stat;
// 	int				infile;
// 	int				outfile;
// 	int				fd_in;
// 	int				fd_out;
// 	int				pfd_in;
// 	int				pfd_out;
// 	pid_t			pid;
// }	t_exec;

////////////////// FONCTIONS //////////////////

//input and parsing
int			only_spaces(char *str);
t_group		*parser(char *input, t_list_env *env);

//envp
char		**get_envp(t_list_env *list);
t_list_env	*get_mini_env();
char		*get_value(char *str);
char		*get_key(char *str);
t_list_env	*get_list(char **tab);
t_list_env	*ft_find_in_env(t_list_env *env, char *target_key);
t_list_env	*ft_new_env_node(char *key, char *value);
int			ft_add_to_msh_env(t_list_env **env, char *new_str);

//builtins
int			is_built(char *str);
int			ft_do_builtin(t_group *group, t_list_env *env, int out_fd);
int			ft_cd(t_group *group, t_list_env *env, int fd);
int			ft_echo(t_group *group, int fd);
int			ft_env(t_group *group, t_list_env *env, int fd);
int			ft_exit(t_group *group);
int			ft_export(t_group *group, t_list_env *env, int fd);
int			ft_pwd(int fd);
int			ft_unset(t_group *group, t_list_env **env);


//fd

//free
void		free_tab(char **tab);
void		free_envp_list(t_list_env *list);
void		free_group_list(t_group *group);

//outils
void		print_env_list(t_list_env *list, int fd);
void		print_tab(char **tab, int fd);
void		ft_putstr_err(char *str);
void		ft_putstr_fd(char *str, int fd);
int			ft_error(char *name, int type, int exit_code);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
int			ft_strlen(const char *s);


#endif