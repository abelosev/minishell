/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   syntax_pb.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/15 21:13:57 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:28:59 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"

void	syntax_pb_msg(char *s)
{
	ft_putstr_err("minishell: syntax error near unexpected token `");
	ft_putstr_err(s);
	ft_putstr_err("'\n");
}

int	syntax_pb(t_tokens *list)
{
	if (list->type == 5)
	{
		syntax_pb_msg(list->value);
		return (1);
	}
	while (list != NULL)
	{
		if ((list->type >= 1 && list->type <= 4 && list->next != NULL
				&& list->next->type != 0) || (list->type != 0
				&& list->next != NULL && list->next->type == 5))
		{
			syntax_pb_msg(list->value);
			return (1);
		}
		if (list->type != 0 && list->next == NULL)
		{
			syntax_pb_msg("newline");
			return (1);
		}
		list = list->next;
	}
	return (0);
}
