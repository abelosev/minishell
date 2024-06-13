/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_x_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memarign <memarign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 04:11:49 by memarign          #+#    #+#             */
/*   Updated: 2024/05/13 04:11:54 by memarign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	group_size(t_group *group)
{
	int	size;

	size = 0;
	while (group != NULL)
	{
		group = group->next;
		size += 1;
	}
	return (size);
}
