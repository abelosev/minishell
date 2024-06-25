/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strncmp.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:53:29 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:03:48 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			break ;
		i++;
	}
	return (0);
}
