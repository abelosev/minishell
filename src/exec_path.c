/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:22:02 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:22:08 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_contains_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_three(char *str1, char *str2, char *str3)
{
	int		str_full_len;
	char	*str_full;
	int		i;
	int		j;

	str_full_len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	str_full = malloc(sizeof(char) * (str_full_len + 1));
	if (!str_full)
	{
		ft_error(NULL, 0, 1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str1[j])
		str_full[i++] = str1[j++];
	j = 0;
	while (str2[j])
		str_full[i++] = str2[j++];
	j = 0;
	while (str3[j])
		str_full[i++] = str3[j++];
	str_full[i] = '\0';
	return (str_full);
}

char	*ft_env_path(char *cmd_name, char **path_vector)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!path_vector)
		return (ft_error(NULL, 0, 1), NULL);
	while (path_vector[i])
	{
		cmd_path = ft_strjoin_three(path_vector[i], "/", cmd_name);
		if (!cmd_path)
		{
			ft_free_char_vector(path_vector);
			return (NULL);
		}
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free_char_vector(path_vector);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_error(cmd_name, 1, 127);
	ft_free_char_vector(path_vector);
	return (NULL);
}

char	*ft_name_path(char *cmd_name)
{
	char		*cmd_path;
	struct stat	buf;

	if (stat(cmd_name, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (NULL);
	if (access(cmd_name, F_OK) != 0)
	{
		ft_error(cmd_name, 0, 127);
		return (NULL);
	}
	cmd_path = ft_strdup(cmd_name);
	if (!cmd_path)
		ft_error(NULL, 0, 1);
	return (cmd_path);
}

char	*ft_find_cmd_path(char *cmd_name, t_env *env)
{
	int		len;
	t_env	*p;

	len = ft_strlen(cmd_name);
	p = env;
	if (len == 0 || (len == 1 && cmd_name[0] == '.'))
		return (ft_error(cmd_name, 1, 127), NULL);
	if (len == 2 && ft_strncmp(cmd_name, "..", 2) == 0)
		return (NULL);
	if (ft_str_contains_char(cmd_name, '/'))
		return (ft_name_path(cmd_name));
	while (p)
	{
		if (ft_strncmp(p->line, "PATH=", 5) == 0)
			break ;
		p = p->next;
	}
	if (!p || p->line == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": No such file or directory\n", 28);
		return (NULL);
	}
	return (ft_env_path(cmd_name, ft_split(p->line + 5, ':')));
}
