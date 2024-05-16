/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_outils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:48:22 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:02:43 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include "../../inc/minishell.h"

void	create_file(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY);
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
