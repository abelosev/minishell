/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:17:57 by abelosev          #+#    #+#             */
/*   Updated: 2021/04/08 12:18:18 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f) (void*), void (*del)(void*))
{
	t_list	*lst1;
	t_list	*lst2;

	if (!lst)
		return (NULL);
	lst1 = NULL;
	while (lst)
	{
		if (!(lst2 = ft_lstnew((*f)(lst->content))))
		{
			while (lst1)
			{
				lst2 = lst1->next;
				(*del)(lst1->content);
				free(lst1);
				lst1 = lst2;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&lst1, lst2);
		lst = lst->next;
	}
	return (lst1);
}
