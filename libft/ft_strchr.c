/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:52:53 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:05:17 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c1;
	int		index;

	c1 = (char)c;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c1)
			return ((char *)(s + index));
		index++;
	}
	if (s[index] == c1)
		return ((char *)(s + index));
	return (NULL);
}
