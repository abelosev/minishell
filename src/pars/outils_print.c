/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:13:46 by abelosev          #+#    #+#             */
/*   Updated: 2024/06/14 04:29:56 by aauthier         ###   ########.fr       */
/*                                                                            */
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
		if(!ft_strchr(list->key, '='))
			ft_putstr_fd("=", fd);
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

void	print_group(t_group *group)
{
	if (group == NULL)
		return ;
	ft_putstr_fd("\nGroup : \n", 0);
	if (group->cmd)
	{
		ft_putstr_fd("\ncmd: \n", STDOUT_FILENO);
		print_tab(group->cmd, STDOUT_FILENO);
	}
	if(group->redir_in)
		printf("fichier redir_in: %s\n", group->redir_in);
	if(group->redir_out)
		printf("fichier redir_out: %s\n", group->redir_out);
	if(group->app_out)
		printf("fichier app_out: %s\n", group->app_out);
	if(group->app_in)
		printf("fichier app_in: %s\n", group->app_in);
	printf("flag_fail: %d\n", group->flag_fail);
}

void	print_group_list(t_group *group)
{
	while(group)
	{
		print_group(group);
		group = group->next;
	}
}
