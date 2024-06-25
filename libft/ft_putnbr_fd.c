/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putnbr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: abelosev <abelosev@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/16 01:52:40 by abelosev		  #+#	#+#			 */
/*   Updated: 2024/06/16 02:10:28 by abelosev		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_leng(long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*fill_up_s(char *s, int len, long n1)
{
	s[len] = '\0';
	while (n1 > 0 && (len-- > 0))
	{
		s[len] = n1 % 10 + 48;
		n1 = n1 / 10;
	}
	return (s);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	n1;
	int		len;
	char	s[13];
	int		i;

	if (n == 0)
		ft_putchar_fd('0', fd);
	n1 = (long)n;
	if (n1 < 0)
	{
		ft_putchar_fd('-', fd);
		n1 *= -1;
	}
	len = ft_leng(n1);
	i = 0;
	while (i <= len)
	{
		s[i] = '\0';
		i++;
	}
	fill_up_s(s, len, n1);
	write(fd, s, ft_strlen(s));
}
