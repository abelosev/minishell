/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:44:10 by memarign          #+#    #+#             */
/*   Updated: 2024/06/04 11:16:41 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

//should be given a delimiter + fd
//delimiter = app_in && fd = exec->fd_in
//read input until a line containing the delimiter is seen
//function to check if delimiter or condition
//exit when delimiter
//print result
//while !is_delimiter get_next_line(fd)
//line = gnl(exec->fdin)
//w/ list = create node, node = line, node = node->next
//print_list
//doesnt have to update history

//do it in a tab with strcpy
//when delimiter return the tab after closing input
//print it

void	print_tab2(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	free_tab(tab);
}

char	**get_here_doc(t_exec *exec, t_group *group)
{
	int		i;
	char	*line;
	char	**here_doc;

	i = 0;
	here_doc = NULL;
	while (1)
	{
		line = get_next_line(exec->fd_in);
		if (line == NULL || ft_strcmp(line, group->app_in) == 0)
		// {
			// free(line);
			break ;
		// }
		else
		{
			here_doc[i] = ft_strdup(line);
			printf("%s", line);
			i++;
		}
		free(line);
	}
	close (exec->fd_in);
	return (here_doc);
}

void	here_doc(t_exec *exec, t_group *group)
{
	char	**tab;

	tab = get_here_doc(exec, group);
	print_tab2(tab);
	free(tab);
}
