#include "../../inc/exec.h"

void	ft_putstr_fd(char *cmd, char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	write(fd, cmd, ft_strlen(cmd));
	write(fd, ": ", 2);
	write(fd, s, i);
	write(fd, ": ", 2);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

int	is_char(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == c)
		i++;
	if (i == ft_strlen(str))
		return (1);
	else
		return (0);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > 32)
			return (1);
		i++;
	}
	return (0);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	group_size(t_group *group)
{
	int	size;

	size = 0;
	while (group != NULL)
	{
		group = group->next;
		size += 1;
	}
	return (size);
}

t_list_env	*ft_lstlast(t_list_env *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list_env **lst, t_list_env *new)
{
	t_list_env	*tmp;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
		else if (!*lst)
			*lst = new;
	}
}
