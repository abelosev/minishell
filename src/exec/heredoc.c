/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:39:12 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 19:53:26 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

unsigned int	g_status;

char	*get_hd_delimiter(t_tokens *list)
{
	char	*del;

	del = NULL;
	while (list->next != NULL)
	{
		if (list->type == 3 && list->next->type == 0)
		{
			if (del && *del)
				free(del);
			del = ft_strdup(list->next->value);
			if (!del)
				return (NULL);
		}
		list = list->next;
	}
	return (del);
}

char	*uniq_name(char *prefix)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin("/tmp/", prefix);
	if (!res)
		return (NULL);
	while (access(res, F_OK) == 0)
	{
		tmp = ft_strjoin(res, prefix);
		free(res);
		if (!tmp)
			return (NULL);
		res = tmp;
	}
	return (res);
}

void	close_hd(int file_fd, int prev_fd, char *del)
{
	close (file_fd);
	signal(SIGINT, SIG_IGN);
	dup2(prev_fd, STDIN_FILENO);
	free(del);
	close(prev_fd);
}

void	do_hd(char *del, t_list_env *env, int file_fd, int *code)
{
	char	*line;
	char	*tmp;

	line = get_line("> ");
	while (line && errno != EINTR && ft_strcmp(line, del))
	{
		tmp = ft_expand(line, env, code);
		if (tmp && *tmp)
			ft_putstr_fd(tmp, file_fd);
		ft_putstr_fd("\n", file_fd);
		if (tmp)
			free(tmp);
		free(line);
		line = readline("> ");
		if (errno == EINTR || errno == EBADF)
		{
			free(line);
			g_status = 130;
		}
	}
}

char	*heredoc(t_list_env *env, char *del, int *code)
{
	char	*file_name;
	int		file_fd;
	int		prev_fd;

	prev_fd = STDIN_FILENO;
	file_name = uniq_name(del);
	prev_fd = dup(STDIN_FILENO);
	file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		free(file_name);
		return (NULL);
	}
	signal(SIGINT, ft_sigint_hd);
	do_hd(del, env, file_fd, code);
	close_hd(file_fd, prev_fd, del);
	return (file_name);
}
