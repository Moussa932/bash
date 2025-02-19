#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	i;

	i = c;
	while (*s)
	{
		if (*s == i)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && i == '\0')
		return ((char *)s);
	return (NULL);
}

static void freetab(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	//free(strs);
}

static int	same(char sep, char c)
{
	if (sep == c)
		return (1);
	return (0);
}

static int	count_word(const char *str, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && same(str[i], sep) == 1)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && same(str[i], sep) == 0)
			i++;
	}
	return (count);
}

static void	tab(char **tab, const char *str, char sep, int leng)
{
	int	i;
	int	j;
	int	k;
	int	m;

	i = 0;
	j = 0;
	while (str[i] != '\0' && j < leng)
	{
		while (str[i] != '\0' && same(sep, str[i]) == 1)
			i++;
		k = i;
		while (str[k] != '\0' && same(sep, str[k]) == 0)
			k++;
		tab[j] = malloc(sizeof(char) * (k - i + 1));
		if (tab[j] == NULL)
			return freetab(tab ,leng);
		m = 0;
		while (i < k)
			tab[j][m++] = str[i++];
		tab[j++][m] = '\0';
	}
	tab[j] = NULL;
}

char	**ft_split(const char *str, char charset)
{
	char	**dest;
	int		leng;

	leng = 0;
	leng = count_word(str, charset);
	dest = malloc(sizeof(char *) * (leng + 1));
	if (dest == NULL)
		return (NULL);
	tab(dest, str, charset, leng);
	return (dest);
}

char *path_in_env(t_env *env)
{
    int i;
    int j;

    j = 0;
    i = var_exist("PATH", &env);
    while(j++ < i)
        env = env -> next;
    return (env -> str);
}

char  *path_search(char **path, t_cmd *cmd , char *command)
{
    int i;
    char *str;

    i = 0;
	str = cmd -> param[0];
	if(access(str, F_OK | X_OK) == 0)
		return str;
	str = NULL;
    while (path[i] && !ft_strchr(cmd -> param[0], '/'))
    {
        str = ft_strjoin(path[i], command);
        if(access(str, F_OK | X_OK) == 0)
            return(str);
		free(str);
        i++;
    }
	return NULL;
}


char *set_path_cmd(t_cmd *cmd, t_env *env)
{
    char **path_env;
    char *path;
    char *command;

	if (!cmd -> param[0])
	{
		ft_putstr_fd("parse error\n", 2);
		exit(2);
	}
    path_env = ft_split(path_in_env(env), ':');
    command = ft_strjoin("/", cmd -> param[0]);
    path = path_search(path_env, cmd, command);
	if (!path)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		if (ft_strchr(cmd -> param[0], '/') != NULL)
			printf("no such file or directory: %s\n", cmd -> param[0]);
		else
			printf("command not found: %s\n", cmd -> param[0]);
		exit(127);
	}
	return path;
}