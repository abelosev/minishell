/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev <abelosev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:46 by abelosev          #+#    #+#             */
/*   Updated: 2024/05/16 14:03:17 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	ft_putstr_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	print_list(t_list_env *list)
{
	while (list != NULL)
	{
		printf("%s", list->key);
		if(!ft_strchr(list->key, '='))
			printf("=");
		printf("%s\n", list->value);
		list = list->next;
	}
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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

void	print_group(t_group *group)
{
	if (group == NULL)
		return ;
	if (group->cmd)
	{
		printf("\ncmd: \n");
		print_tab(group->cmd);
	}
	printf("fichier redir_in: %s\n", group->redir_in);
	printf("fichier redir_out: %s\n", group->redir_out);
	printf("fichier app_out: %s\n", group->app_out);
	printf("flag: %d\n", group->flag_fail);
}
