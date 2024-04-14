#include "../inc/parsing.h"

int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_digit(char c)
{
    return (c >= '1' && c <= '9');
}

int ft_strlen(const char *s)
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*s;
	size_t	len;
	size_t	i;

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

char **copy_tab(char **tab)
{
	int nb_line;
	int i;
	char **copy;

	nb_line = 0;
	i = 0;
	while(tab[nb_line])
		nb_line++;
	copy = malloc(sizeof(char **) * (nb_line));
	while(i < nb_line && tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int		ft_strncmp(const char *s1, const char *s2, int n)
{
	int i;

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	res = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	k;

	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	res = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		res[i + k] = s2[k];
		k++;
	}
	res[i + k] = '\0';
	return (res);
}
