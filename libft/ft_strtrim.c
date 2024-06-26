/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:53:42 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:00:50 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_check_chr(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*full_blank_input(void)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * 1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*create_s(char const *s1, int end_s, int start_s)
{
	char	*s;
	int		i;

	s = (char *)malloc(sizeof(char) * (end_s - start_s + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i + start_s] && i + start_s < end_s)
	{
		s[i] = s1[i + start_s];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		start_s;
	int		end_s;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start_s = 0;
	while (s1[start_s] && (ft_check_chr(s1[start_s], set) == 1))
		start_s++;
	end_s = (int)ft_strlen(s1);
	while (end_s >= 0 && ft_check_chr(s1[end_s - 1], set) == 1)
		end_s--;
	if (end_s - start_s <= 0)
		s = full_blank_input();
	else
		s = create_s(s1, end_s, start_s);
	return (s);
}
