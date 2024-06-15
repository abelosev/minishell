/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_outils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:48:22 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/15 21:18:57 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	create_file(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	close(fd);
}

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
