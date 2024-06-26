/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   expand.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 02:22:28 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 19:48:12 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

char	*no_null(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = 28;
	str[1] = '\0';
	return (str);
}

char	*expanded_token(char *str, t_list_env *env)
{
	char	*res;

	res = no_null();
	while (env != NULL)
	{
		if (ft_strncmp(env->key, str, ft_strlen(str)) == 0)
		{
			free(res);
			res = ft_strdup(env->value);
			break ;
		}
		else
			env = env->next;
	}
	return (res);
}

static void	replace_token(char **str, t_list_env *env, int *code)
{
	int		i;
	char	*new;

	i = 0;
	if ((*str)[i] != '$')
		new = ft_strdup((*str));
	else if ((*str)[i] == '$' && (*str)[i + 1] == '\0')
		new = ft_strdup((*str));
	else
	{
		if ((*str)[i + 1] && ft_isdigit((*str)[i + 1]))
			new = no_null();
		else if ((*str)[i + 1] && ft_isalpha((*str)[i + 1]))
			new = expanded_token((*str) + 1, env);
		else if ((*str)[i + 1] && (*str)[i + 1] == '?')
			new = ft_itoa(*code);
		else
			new = no_null();
	}
	free((*str));
	(*str) = new;
}

char	*from_tab_to_line(char **tab)
{
	int		i;
	char	*res;
	char	*temp;
	char	*t;

	temp = no_null();
	res = ft_strdup(tab[0]);
	i = 1;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], temp, ft_strlen(tab[i]) != 0))
		{
			t = res;
			res = ft_strjoin(t, tab[i]);
			free(t);
		}
		i++;
	}
	free(temp);
	free_tab(tab);
	return (res);
}

char	*ft_expand(char *str, t_list_env *env, int *code)
{
	char	*temp;
	char	**token_tab;
	char	*new;
	int		i;

	temp = temp_tokenizer(str);
	if (!temp)
		return (NULL);
	token_tab = ft_split1(temp, 3);
	if (!token_tab || !token_tab[0])
	{
		free(token_tab);
		free(temp);
		return (NULL);
	}
	i = 0;
	while (token_tab[i])
	{
		replace_token(token_tab + i, env, code);
		i++;
	}
	free(temp);
	new = from_tab_to_line(token_tab);
	return (new);
}
