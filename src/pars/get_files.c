/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:18 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:02:48 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include "../../inc/minishell.h"

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

int	handle_outfile(char **s1, char **s2, char **s3, t_tokens *list)
{
	*s1 = outfile_access(list, *s1);
	if (*s1 == NULL)
	{
		if (*s2)
			free(*s2);
		if (*s3)
			free(*s3);
		return (1);
	}
	create_file(*s1);
	return (0);
}

int	handle_infile(t_tokens *list, t_group *group)
{
	group->redir_in = infile_access(list, group->redir_in);
	if (group->redir_in == NULL)
	{
		if (group->redir_out)
			free(group->redir_out);
		if (group->app_out)
			free(group->app_out);
		return (1);
	}
	return (0);
}

int	get_hd_delimiter(t_tokens *list, t_group *group)	//добавить перезапись делимитера
{
	while (list->type != 5 && list->next != NULL)
	{
		if(list->type == 3 && list->next->type == 0)
		{
			group->app_in = ft_strdup(list->next->value);
			if(!group->app_in)
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	get_files(t_tokens *list, t_group *group)
{
	while (list->type != 5 && list->next != NULL)
	{
		if (list->type == 1 && list->next->type == 0)
		{
			if (handle_infile(list, group))
				return (1);
		}
		else if (list->type == 2 && list->next->type == 0)
		{
			if (handle_outfile(&group->redir_out, &group->redir_in,
					&group->app_out, list))
				return (1);
		}
		else if (list->type == 4 && list->next->type == 0)
		{
			if (handle_outfile(&group->app_out, &group->redir_in,
					&group->redir_out, list))
				return (1);
		}
		list = list->next;
	}
	return (0);
}
