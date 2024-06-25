/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strnstr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:53:34 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 01:57:17 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	l;
	int	i;

	if (needle[0] == '\0' || !needle)
		return ((char *)(haystack));
	i = 0;
	while (haystack[i])
	{
		l = 0;
		while (needle[l] == haystack[i + l] && (l < len))
		{
			if (ft_strlen(needle) + i > len)
				return (0);
			if (!needle[l + 1])
				return ((char *)(haystack + i));
			l++;
		}
		i++;
	}
	return (NULL);
}
