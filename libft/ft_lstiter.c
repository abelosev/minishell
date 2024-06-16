/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:51:28 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/16 02:09:35 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	t_list	*new;

	new = lst;
	if (!new)
		return ;
	while (new != NULL)
	{
		(*f)(new->content);
		new = new->next;
	}
}
