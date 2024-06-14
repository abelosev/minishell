#include "minishell.h"

int		ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
	(c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	c1;
	int	index;

	c1 = (char)c;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c1)
			return ((char*)(s + index));
		index++;
	}
	if (s[index] == c1)
		return ((char*)(s + index));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*s;
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(s1);
	s = (char*)malloc(sizeof(*s1) * (len + 1));
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
