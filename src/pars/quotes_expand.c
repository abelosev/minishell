/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   quotes_expand.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/16 12:15:09 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 19:51:10 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"

void	temp_free(char *a, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

char	*quotes_handle(char *str)
{
	char	*replaced;
	char	*no_double;

	replaced = NULL;
	no_double = NULL;
	replaced = add_spaces(&str);
	if (replaced == NULL)
		return (NULL);
	no_double = no_quotes(replaced, 29);
	if (no_double == NULL || *no_double == '\0')
	{
		free(replaced);
		if (no_double)
			free(no_double);
		return (NULL);
	}
	free(replaced);
	return (no_double);
}

char	*expnd_handle(char *no_double, t_list_env *env, int *code)
{
	char	*no_single;
	char	*expnd;

	no_single = NULL;
	expnd = NULL;
	expnd = ft_expand(no_double, env, code);
	if (expnd == NULL || *expnd == '\0')
	{
		free(expnd);
		return (NULL);
	}
	no_single = no_quotes(expnd, 30);
	if (no_single == NULL || *no_single == '\0')
	{
		free(expnd);
		if (no_single)
			free(no_single);
		return (NULL);
	}
	free(expnd);
	return (no_single);
}

char	*quotes_expand(char *str, t_list_env *env, int *code)
{
	char	*no_double;
	char	*no_single;

	no_double = NULL;
	no_single = NULL;
	no_double = quotes_handle(str);
	if (no_double == NULL)
		return (NULL);
	no_single = expnd_handle(no_double, env, code);
	if (no_single == NULL)
	{
		if (no_double)
			free(no_double);
		return (NULL);
	}
	free(no_double);
	return (no_single);
}
