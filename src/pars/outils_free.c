/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   outils_free.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 02:23:27 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/24 17:56:10 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	if (tab && !(*tab))
	{
		free(tab);
		return ;
	}
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_int(int **tab, int len)
{
	int	i;

	if (!tab)
		return ;
	if (tab && !(*tab))
	{
		free(tab);
		return ;
	}
	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tokens(t_tokens *list)
{
	t_tokens	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		if (list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}

void	free_envp_list(t_list_env *list)
{
	t_list_env	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		if (list->key)
			free(list->key);
		if (list->value)
			free(list->value);
		free(list);
		list = tmp;
	}
}
