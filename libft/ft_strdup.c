/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strdup.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:52:57 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:11:09 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	s = (char *)malloc(sizeof(*s1) * (len + 1));
	if (s == NULL)
		return (NULL);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
