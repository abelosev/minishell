#include "../../inc/exec.h"
// #include "../../inc/parsing.h"

//env when env -i
//SHLVL += 1
t_list_env	*env_lst_sos(void)
{
	char		*buf;
	size_t		size;
	t_list_env	*env_lst;

	buf = NULL;
	size = 0;
	env_lst = malloc(sizeof(t_list_env));
	if (!env_lst)
		return (NULL);
	env_lst->key = "PWD";
	env_lst->value = getcwd(buf, size);
	env_lst->next = malloc(sizeof(t_list_env));
	if (!env_lst->next)
	{
		free(buf);
		return (NULL);
	}
	env_lst->next->key = "SHLVL";
	env_lst->next->value = "1";
	env_lst->next->next = NULL;
	free(buf);
	return (env_lst);
}

//env for pgm
//just env_lst sos
//return list
t_list_env	*set_envp(char **envp)
{
	t_list_env	*env;

	if (*envp == NULL)
		env = env_lst_sos();
	else
		env = get_list(envp);
	return (env);
}

//return var or end of list if !var
t_list_env	*check_var(t_list_env **env_lst, char *var)
{
	while ((*env_lst)->next != NULL)
	{
		// printf("check key = %s\n", (*env_lst)->key);
		if (ft_strncmp((*env_lst)->key, get_key(var), ft_strlen(var)) == 0)
				return (*env_lst);
		else
			*env_lst = (*env_lst)->next;
	}
	return (*env_lst);
}

//modify or add var
void	mod_var(t_list_env **env_lst, char *var)
{
	t_list_env	*new;

	if (!(*env_lst)->next)
	{
		new = malloc(sizeof(t_list_env));
		if (!new)
			return ;
		ft_lstadd_back(env_lst, new);
		// (*env_lst) = (*env_lst)->next;
		new->key = ft_strdup(get_key(var));
		new->value = ft_strdup(get_value(var));
		new->next = NULL;
	}
	else
	{
		free((*env_lst)->value);
		(*env_lst)->value = ft_strdup(get_value(var));
	}
	// free_envp_list(new);
}

//handle = + void?
t_list_env	*remove_first(t_list_env **env_lst)
{
	t_list_env	*tmp;

	tmp = *env_lst;
	(*env_lst) = (*env_lst)->next;
	free(tmp->key);
	free(tmp->value);
	return(*env_lst);
}

void	remove_var(t_list_env **env_lst)
{
	if (!(*env_lst)->next)
	{
		free((*env_lst)->key);
		free((*env_lst)->value);
		// (*env_lst) = NULL;
	}
	else
	{
		free((*env_lst)->key);
		free((*env_lst)->value);
		(*env_lst) = (*env_lst)->next;
	}
}
