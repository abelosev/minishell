/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser_outils.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 02:28:17 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 20:35:37 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "parsing.h"

int	only_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

t_parser	*create_init_p(void)
{	
	t_parser	*p;

	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->line = NULL;
	p->token_tab = NULL;
	p->token_list = NULL;
	return (p);
}

t_main	*create_init_m(t_parser *p)
{
	t_main	*m;

	m = malloc(sizeof(t_main));
	if (!m)
	{
		free_t_parser(p);
		return (NULL);
	}
	m->group = NULL;
	m->hd_del = NULL;
	m->group = create_init_group();
	if (!m->group)
	{
		free_t_parser(p);
		free(m);
		return (NULL);
	}
	return (m);
}

char	**spaces_between_quotes(char ***tab)
{
	int	i;
	int	k;

	i = 0;
	while ((*tab)[i])
	{
		k = 0;
		while ((*tab)[i][k] != '\0')
		{
			if ((*tab)[i][k] == 27)
				(*tab)[i][k] = ' ';
			k++;
		}
		i++;
	}
	return (*tab);
}
