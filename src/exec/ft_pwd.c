/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:20:19 by aauthier          #+#    #+#             */
/*   Updated: 2024/06/16 19:14:04 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_error("pwd", 0, 1));
	write(fd, current_dir, ft_strlen(current_dir));
	write(fd, "\n", 1);
	free(current_dir);
	return (0);
}
