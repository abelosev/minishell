#include "../../inc/minishell.h"

void	ft_write_export(t_env *env, int fd)
{
	t_env	*p;

	p = env;
	while (p)
	{
		write(fd, "declare -x ", 11);
		write(fd, p->line, ft_strlen(p->line));
		write(fd, "\n", 1);
		p = p->next;
	}
}

int	ft_export_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		write(2, "minishell: export: `", 20);
		write(2, str, ft_strlen(str));
		write(2, "\': not a valid identifier\n", 26);
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write(2, "minishell: export: `", 20);
			write(2, str, ft_strlen(str));
			write(2, "\': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_replace_or_add(t_env *env, char *str)
{
	char	*str_copy;
	t_env	*the_env;
	int		len;

	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	the_env = ft_find_in_env(env, str, len);
	str_copy = ft_strdup(str);
	if (!str_copy)
		return (ft_error(NULL, 0, 1));
	if (the_env != NULL)
	{
		free(the_env->line);
		the_env->line = str_copy;
		return (0);
	}
	return (ft_add_to_msh_env(env, str_copy));
}

int	ft_export(char **args, t_env *env, int fd)
{
	int		i;
	int		error_flag;

	if (args[1] == NULL)
		return (ft_write_export(env, fd), 0);
	i = 1;
	error_flag = 0;
	while (args[i] != NULL)
	{
		if (ft_export_is_valid(args[i]))
		{
			if (ft_export_replace_or_add(env, args[i]))
				return (1);
		}
		else
			error_flag = 1;
		i++;
	}
	return (error_flag);
}
