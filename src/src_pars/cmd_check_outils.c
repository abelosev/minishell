/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check_outils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:31:05 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:02:10 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	is_built(char *str)
{
	int		i;
	char	*tab[7];

	i = 0;
	tab[0] = "env";
	tab[1] = "pwd";
	tab[2] = "echo";
	tab[3] = "unset";
	tab[4] = "export";
	tab[5] = "cd";
	tab[6] = "exit";
	while (i <= 6)
	{
		if (ft_strcmp(str, tab[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_folder(char *line)
{
	int	fd;
	int	res;
	DIR	*d;

	if (!line || *line == '\0')
		return (0);
	fd = open(line, O_WRONLY);
	d = opendir(line);
	if (fd == -1 && d != NULL)
	{
		ft_putstr_err("minishell: ");
		ft_putstr_err(line);
		ft_putstr_err(": Is a directory\n");
		res = 1;
	}
	else
		res = 0;
	if (fd > 0)
		close(fd);
	if (d)
		closedir(d);
	return (res);
}

int	cmd_lines_nb(t_tokens *list)
{
	int	len;

	len = 0;
	while (list != NULL && list->type == 0)
	{
		len++;
		list = list->next;
	}
	return (len);
}

char	**get_cmd_tab(t_tokens *list)
{
	int			len;
	int			i;
	char		**cmd_tab;

	len = 0;
	i = 1;
	while (list != NULL && list->next != NULL && list->type != 0
		&& list->next->type == 0)
		list = list->next->next;
	if (list == NULL)
		return (NULL);
	len = cmd_lines_nb(list);
	cmd_tab = malloc(sizeof(char *) * (len + 1));
	if (!cmd_tab)
		return (NULL);
	cmd_tab[0] = ft_strdup(list->value);
	list = list->next;
	while (i < len && list != NULL)
	{
		cmd_tab[i] = ft_strdup(list->value);
		i++;
		list = list->next;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}
