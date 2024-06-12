/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:32:07 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 10:39:48 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_cmd **cmd_list, t_env *env)
{
	int		i;
	t_token	*head;
	t_token	*temp;

	if (env != NULL)
		ft_free_envp(env);
	i = 0;
	if (cmd_list != NULL)
	{
		while (cmd_list[i])
		{
			head = cmd_list[i]->tokens;
			while (head)
			{
				temp = head;
				head = head->next;
				if (temp->word != NULL)
					free(temp->word);
				free(temp);
			}
			free(cmd_list[i]);
			i++;
		}
	}
	free(cmd_list);
}

void	ft_close_all(t_cmd **cmd_list)
{
	int		i;
	t_token	*t;

	i = 0;
	while (cmd_list[i])
	{
		if (cmd_list[i]->in_fd > 2)
			close(cmd_list[i]->in_fd);
		if (cmd_list[i]->out_fd > 2)
			close(cmd_list[i]->out_fd);
		t = cmd_list[i]->tokens;
		while (t)
		{
			if (t->fd > 2)
				close(t->fd);
			t = t->next;
		}
		i++;
	}
}

void	ft_free_char_vector(char **args)
{
	int	i;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

int	ft_error(char *name, int type, int exit_code)
{
	if (type == 0)
	{
		if (name == NULL)
			perror("minishell");
		else
		{
			write(2, "minishell: ", 11);
			perror(name);
		}
	}
	if (type == 1 && name)
	{
		write(2, "minishell: ", 11);
		write(2, name, ft_strlen(name));
		write(2, ": command not found\n", 20);
	}
	return (exit_code);
}

void	ft_free_char_vector_index(char **vector, int i)
{
	while (i >= 0)
	{
		free(vector[i]);
		i--;
	}
	free(vector);
}
