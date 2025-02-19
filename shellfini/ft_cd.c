#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char  *tmp_oldpwd()
{
	char buff[PATH_MAX];
	char *tmp;

	if(getcwd(buff, PATH_MAX))
		tmp = ft_strjoin("OLDPWD=", buff);
	return tmp;
}

int get_pwd(char *str, t_env *env, char *oldpwd)
{
    char buff[PATH_MAX];
    char *tmp;
	int i;

	i = var_exist("OLDPWD=", &env);
	update_env(&env, i, oldpwd);
    if(!getcwd(buff, PATH_MAX))
    {
        printf("%s\n", strerror(errno));
        return -1;
    }
    tmp = ft_strjoin("PWD=", buff);
	i = var_exist("PWD=", &env);
	update_env(&env, i, tmp);
	free(tmp);
	return 0;
}

int ft_cd(t_cmd *cmd, t_data *data)
{
    t_env *envi;
	char *str;

	envi = data -> envlist;
	str = tmp_oldpwd();
    if (chdir(cmd -> param[1]) == -1)
	{
		printf("%s\n",strerror(errno));
		return 1;
	}
    if(get_pwd(cmd -> param[1], envi, str) == -1)
	{
		free(str);
		return 1;
	}
	free(str);
    return (0);
}