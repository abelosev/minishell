/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_set_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:30:27 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 10:38:32 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_file(t_cmd **cmd_list, int i, char *filename, enum e_type type)
{
	int	fd;

	fd = 0;
	if (type == FILE_IN)
		fd = open(filename, O_RDONLY);
	if (type == FILE_OUT)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (type == FILE_OUT_AP)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (fd < 0)
		return (ft_error(filename, 0, 1));
	if (type == FILE_OUT || type == FILE_OUT_AP)
	{
		if (cmd_list[i]->out_fd != 1)
			close(cmd_list[i]->out_fd);
		cmd_list[i]->out_fd = fd;
	}
	if (type == FILE_IN)
	{
		if (cmd_list[i]->in_fd != 0)
			close(cmd_list[i]->in_fd);
		cmd_list[i]->in_fd = fd;
	}
	return (0);
}

int	ft_set_io(t_cmd **cmd_list, int i, int single_flag)
{
	t_token	*t;
	int		exit_status;

	t = cmd_list[i]->tokens;
	exit_status = 0;
	while (t != NULL && exit_status == 0)
	{
		if (t->type == DELIMITER && find_space(t->word))
			return (ft_ambig(t->word), 1);
		if (t->type == FILE_IN || t->type == FILE_OUT || t->type == FILE_OUT_AP)
			exit_status = ft_file(cmd_list, i, t->word, t->type);
		if (t->type == DELIMITER || t->type == DELIMITER_Q)
		{
			if (cmd_list[i]->in_fd != 0)
				close(cmd_list[i]->in_fd);
			cmd_list[i]->in_fd = t->fd;
			t->fd = 0;
		}
		t = t->next;
	}
	if (exit_status == 0)
		ft_dup(cmd_list, i, single_flag);
	return (exit_status);
}

int	ft_heredoc(char *limitor, enum e_type type, int old_exit, t_env *msh_env)
{
	int		pipe_ends[2];
	char	*str;
	size_t	len;

	if (pipe(pipe_ends))
		return (ft_error(NULL, 0, 0));
	len = ft_strlen(limitor);
	str = readline("> ");
	if (g_signal)
		return (close(pipe_ends[0]), close(pipe_ends[1]), 0);
	while (str && !(len == ft_strlen(str) && !ft_strncmp(limitor, str, len)))
	{
		str = ft_heredoc_expand(str, type, msh_env, old_exit);
		if (ft_hdoc_write(str, pipe_ends) == 0)
			str = readline("> ");
		else if (g_signal || !str)
			return (close(pipe_ends[0]), close(pipe_ends[1]), 0);
	}
	if (!str)
		return (ft_hdoc_sig(limitor), close(pipe_ends[1]), pipe_ends[0]);
	return (free(str), close(pipe_ends[1]), pipe_ends[0]);
}

int	ft_set_hdoc(t_cmd **cmd_list, int e, t_env *msh_env)
{
	int		i;
	t_token	*token;

	i = 0;
	while (cmd_list[i])
	{
		token = cmd_list[i]->tokens;
		while (token)
		{
			if (token->type == DELIMITER || token->type == DELIMITER_Q)
			{
				token->fd = ft_heredoc(token->word, token->type, e, msh_env);
				if (token->fd == 0)
					return (1);
			}
			token = token->next;
		}
		i++;
	}
	return (0);
}
