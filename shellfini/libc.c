#include "minishell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char *ft_strdup(char *src)
{
    int i;
    char *dest;

    if (!src)
        return NULL;
    i = 0;
    dest = malloc(sizeof(char) * ft_strlen(src) + 1);
    if (!src)
        return NULL;
    while (src[i])
    {
        dest[i] =  src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int ft_strncmp(char *s1, char *s2, int length)
{
    int i;
    if (!s1 || !s2 || length < 0)
        return 0;
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i] && i < length - 1)
        i++;
    return (s1[i] - s2[i]);
}


static int	count_nbr(int nbr)
{
	int				count;
	unsigned int	n;

	count = 1;
	if (nbr < 0)
	{
		n = -nbr;
		++count;
	}
	else
		n = nbr;
	while (n >= 10)
	{
		n /= 10;
		++count;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	t;

	i = count_nbr(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		t = -n;
	else
		t = n;
	str[i] = '\0';
	while (--i >= 0)
	{
		str[i] = (t % 10) + 48;
		t /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (start + i < ft_strlen(s) && i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}