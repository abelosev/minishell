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
	ft_putstr_fd("Parsed: \n", 0);
	if (group->cmd)
	{
		ft_putstr_fd("\ncmd: \n", STDOUT_FILENO);
		print_tab(group->cmd, STDOUT_FILENO);
	}
	ft_putstr_fd("fichier redir_in: ", STDOUT_FILENO);
	ft_putstr_fd(group->redir_in, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("fichier redir_out: ", STDOUT_FILENO);
	ft_putstr_fd(group->redir_out, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("fichier app_out: ", STDOUT_FILENO);
	ft_putstr_fd(group->app_out, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("fichier app_in: \n", STDOUT_FILENO);
	ft_putstr_fd(group->app_in, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("flag: ", STDOUT_FILENO);
	ft_putstr_fd(ft_itoa(group->flag_fail), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
