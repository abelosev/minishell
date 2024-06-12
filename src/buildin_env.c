/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:13:33 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/02 12:28:21 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env *env, int fd)
{
	t_env	*p;

	p = env;
	if (args[1] != NULL)
	{
		write(2, "env: warning: additional arguments to env are ignored\n", 54);
		return (127);
	}
	while (p)
	{
		if (ft_str_contains_char(p->line, '='))
		{
			write(fd, p->line, ft_strlen(p->line));
			write(fd, "\n", 1);
		}
		p = p->next;
	}
	return (0);
}
