/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstmap.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:51:38 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:10:10 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void*), void (*del)(void*))
{
	t_list	*lst1;
	t_list	*lst2;

	if (!lst)
		return (NULL);
	lst1 = NULL;
	while (lst)
	{
		lst2 = ft_lstnew((*f)(lst->content));
		if (!lst2)
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
