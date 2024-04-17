/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:18 by abelosev          #+#    #+#             */
/*   Updated: 2024/04/15 21:38:48 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

void	permission_pb_msg(char *str)
{
	ft_putstr_err("minishell: ");
	ft_putstr_err(str);
	ft_putstr_err(": Permission denied\n");
}

void	existence_pb_msg(char *str)
{
	ft_putstr_err("minishell: ");
	ft_putstr_err(str);
	ft_putstr_err(": No such file or directory\n");
}

char	*outfile_access(t_tokens *list, char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if (!str)
		return (NULL);
	if (access(str, F_OK) != 0)
		return (str);
	else if (access(str, R_OK | W_OK) != 0)
	{
		permission_pb_msg(str);
		free(str);
		return (NULL);
	}
	return (str);
}

char	*infile_access(t_tokens *list, char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	str = ft_strdup(list->next->value);
	if (!str)
		return (NULL);
	if (access(str, F_OK) != 0)
	{
		existence_pb_msg(str);
		free(str);
		return (NULL);
	}
	else if (access(str, R_OK | W_OK) != 0)
	{
		permission_pb_msg(str);
		free(str);
		return (NULL);
	}
	return (str);
}

int	get_files(t_tokens *list, t_group *group)
{
	while (list->type != 5 && list->next != NULL)
	{
		if (list->type == 1 && list->next->type == 0)
		{
			group->redir_in = infile_access(list, group->redir_in);
			if (group->redir_in == NULL)
				return (1);
		}
		else if (list->type == 2 && list->next->type == 0)
		{
			group->redir_out = outfile_access(list, group->redir_out);
			if (group->redir_out == NULL)
				return (1);
		}
		else if (list->type == 4 && list->next->type == 0)
		{
			group->app_out = outfile_access(list, group->app_out);
			if (group->app_out == NULL)
				return (1);
		}
		list = list->next;
	}
	return (0);
}
