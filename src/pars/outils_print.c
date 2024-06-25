/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   outils_print.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 02:28:11 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 19:31:30 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"

void	ft_putstr_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	print_env_list(t_list_env *list, int fd)
{
	while (list != NULL)
	{
		ft_putstr_fd(list->key, fd);
		if (!ft_strchr(list->key, '='))
			ft_putstr_fd("=", fd);
		if (list->value)
			ft_putstr_fd(list->value, fd);
		ft_putstr_fd("\n", fd);
		list = list->next;
	}
}

void	print_tab(char **tab, int fd)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		ft_putstr_fd(tab[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	ft_putstr_fd("\n", fd);
}

void	print_token_list(t_tokens *list)
{
	while (list != NULL)
	{
		printf("%u", list->type);
		printf("=");
		printf("%s\n", list->value);
		list = list->next;
	}
}
