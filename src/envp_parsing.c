#include "../inc/parsing.h"

int separate_pos(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char *get_key(char *str)
{
	int len;
	int k;
	char *key;

	len = separate_pos(str); //добавлять ли обработку случая, когда separate_pos < 0?
	k = 0;
	key = malloc(sizeof(char) * (len + 1));
	if(!key)
		return (NULL);
	while(k < len && str[k])
	{
		key[k] = str[k];
		k++;
	}
	key[k] = '\0';
	return (key);
}

char *get_value(char *str)
{
	char *value;
	int i;
	int k;
	int len;

	i = separate_pos(str) + 1;
	k = 0;
	len = ft_strlen(str) - i;

	value = malloc(sizeof(char) * (len + 1));
	if(!value)
		return (NULL);
	while(k < len)
	{
		value[k] = str[i];
		k++;
		i++;
	}
	value[k] = '\0';
	return (value);
}

t_list_env *get_list(char **tab)
{
	int i;
	t_list_env *begin;
	t_list_env *curr;

	i = 0;
	begin = malloc(sizeof(t_list_env));
	if(!begin)
		return (NULL);
	begin->key = get_key(tab[0]);
	begin->value = get_value(tab[0]);
	begin->next = NULL;
	curr = begin;
	i = 1;
	while(tab[i])
	{
		curr->next = malloc(sizeof(t_list_env));
		if(!curr->next)
		{
			free_envp_list(begin);
			return (NULL);
		}
		curr = curr->next;
		curr->key = get_key(tab[i]);
		curr->value = get_value(tab[i]);
		i++;
	}
	curr->next = NULL;
	return(begin);
}

//функция конвертации t_list_env *list в char **envp


int get_line_len(char *s1, char *s2)
{
	return (ft_strlen(s1) + ft_strlen(s2) + 2);
}

int get_node_nb(t_list_env *list)
{
	int node_nb;

	node_nb = 0;
	while(list != NULL)
	{
		list = list->next;
		node_nb++;
	}
	return (node_nb);
}

char **get_envp(t_list_env *list)
{
	char **envp;
	char *tmp1;
	int i;

	i = 0;
	envp = malloc(sizeof(char*) * (get_node_nb(list) + 1));
	if(!envp)
		return (NULL);
	while(list != NULL)
	{
		tmp1 = ft_strjoin(list->key, "=");
		envp[i] = ft_strjoin(tmp1, list->value);
		free(tmp1);
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}