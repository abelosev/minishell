#include "../inc/parsing.h"

char	**get_path(char **envp)
{
	char	**res;

	res = NULL;
	if (envp == NULL || *envp == NULL)
	{
		perror("Envp");
		return (NULL);
	}
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			res = ft_split1(*envp + 5, 2);
			if (res != NULL)
				return (res);
		}
		envp++;
	}
	return (NULL);
}

//arg_w_path - это первый аргумент execve

char	*path_check(char **path_list, char **args_list) //вместо args_list char **lg->cmd
{
	char	*arg_w_path;
	char	*prefix;
	int		i;

	arg_w_path = NULL;
	i = 0;
	while (path_list[i])
	{
		prefix = ft_strjoin(path_list[i], "/");
		arg_w_path = ft_strjoin(prefix, args_list[0]);
		if (access(arg_w_path, F_OK) == 0)
		{
			free(prefix);
			return (arg_w_path);
		}
		else
		{
			free(prefix);
			free(arg_w_path);
			i++;
		}
	}
	return (NULL);
}

/*char	**args_list_check(char *arg)
{
	char	**args_list;

	args_list = ft_split(arg, 1);
	if (args_list == NULL)
	{	
		perror("Error");
		return (NULL);
	}
	if (args_list[0] == NULL)
	{
		free_array(args_list);
		return (NULL);
	}
	return (args_list);
}*/

char	*cmd_check(char **cmd, char **envp)
{
	char	**path_list;
	char	*arg_w_path;
	//char	**args_list;

	arg_w_path = NULL;
	path_list = get_path(envp);
	if (path_list == NULL)
	{
		perror("Error");
		return (NULL);
	}
	if (cmd[0][0] == '/' && (access(cmd[0], F_OK) == 0))
		arg_w_path = ft_strdup(cmd[0]);
	else
		arg_w_path = path_check(path_list, cmd);
	free_tab(path_list);
	return (arg_w_path);
}