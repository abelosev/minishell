#include "../../inc/minishell.h"

int		ft_len(int n)
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

char	*ft_itoa_zero(void)
{
	char	*s;

	s = (char*)malloc(sizeof(char) * 2);
	if (s == NULL)
		return (NULL);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*fill_up_array(long n1, int len, char *s)
{
	if (n1 < 0)
	{
		s[0] = '-';
		n1 *= -1;
	}
	while (n1 > 0 && (--len >= 0))
	{
		s[len] = n1 % 10 + 48;
		n1 = n1 / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		len;
	long	n1;
	char	*s;

	n1 = (long)n;
	if (n1 == 0)
		return (ft_itoa_zero());
	len = ft_len(n);
	if (n1 < 0)
		len += 1;
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	return (fill_up_array(n1, len, s));
}
