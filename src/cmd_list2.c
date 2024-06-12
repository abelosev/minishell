/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:31:46 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 10:32:07 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*strct;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		strct = ft_lstlast_cmd(*lst);
		strct->next = new;
	}
}

void	free_cmd_list(t_cmd **lst)
{
	t_cmd	*strct;

	if (!lst)
		return ;
	strct = *lst;
	while (strct)
	{
		strct = strct->next;
		free_cmd(*lst);
		*lst = strct;
	}
	*lst = NULL;
}

int	ft_lstsize_cmd(t_cmd *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
