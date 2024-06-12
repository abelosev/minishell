/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 09:44:27 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/04 15:44:05 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *word, t_env *env)
{
	int		pos;
	int		var_len;
	char	*var_value;
	t_env	*p;

	pos = 1;
	var_len = ft_strlen(word) - 1;
	var_value = NULL;
	p = env;
	while (p)
	{
		if (ft_strncmp((word + pos), p->line, var_len) == 0
			&& *(p->line + var_len) == '=')
		{
			var_value = ft_strdup(p->line + (var_len + pos));
			break ;
		}
		p = p->next;
	}
	if (var_value == NULL)
		var_value = ft_strdup("\0");
	return (var_value);
}

char	*ft_get_uid(t_env *env)
{
	char	*var_value;
	char	*uid_line;
	int		var_len;
	t_env	*p;

	uid_line = "XDG_RUNTIME_DIR=/run/user/";
	var_len = ft_strlen(uid_line);
	var_value = NULL;
	p = env;
	while (p)
	{
		if (ft_strncmp(uid_line, p->line, var_len) == 0)
		{
			var_value = ft_strdup(p->line + (var_len));
			break ;
		}
		p = p->next;
	}
	if (var_value == NULL)
		var_value = ft_strdup("\0");
	return (var_value);
}

void	switch_arg_env(char **word, t_env *env, int exit_code)
{
	char	*var_value;

	if ((*word)[1] == '$')
		var_value = ft_itoa(getpid());
	else if ((*word)[1] == '?')
		var_value = ft_itoa(exit_code);
	else if (ft_isdigit((*word)[1]))
		var_value = ft_strdup("\0");
	else if (ft_strncmp((*word + 1), "UID", 4) == 0)
		var_value = ft_get_uid(env);
	else
		var_value = get_env_value(*word, env);
	free(*word);
	*word = var_value;
}

void	ft_process_env(t_token *pre, t_env *env, int exit_code)
{
	t_token	*p;

	p = pre;
	while (p)
	{
		if ((p->word[0]) == '$' && p->word[1])
			switch_arg_env(&(p->word), env, exit_code);
		p = p->next;
	}
}

void	expansion(char **word, t_env *env, int exit_code)
{
	t_token	*pre;
	char	*new;

	if (check_expansion_sign(*word) == 0)
		return ;
	pre = ft_divide_arg_env(*word);
	ft_process_env(pre, env, exit_code);
	new = ft_combine(pre);
	ft_token_free_lst(pre);
	free(*word);
	*word = new;
}
