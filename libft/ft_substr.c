/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_substr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:53:46 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:04:58 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*res;
	int		i;

	if (s == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(*s) * (len + 1));
	if (res == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		res[0] = '\0';
		return (res);
	}
	i = 0;
	while (s[start + i] != '\0' && (i < len))
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
