#include "minishell.h"

int ft_env(t_cmd *cmd, t_data *data)
{
    t_env *envi;

    envi = data -> envlist;
    if(cmd -> param[1] != NULL)
    {
        printf("error to many argument\n");
        return (1);
    }
    while(envi)
    {
        if (envi -> str != NULL)
            printf("%s\n", envi -> str);
        envi = envi -> next;
    }
    return (0);
}

char **copy_arg_env(t_data *data)
{
    int i;
    t_env *env;
    char **dest;

    i = 0;
    env = data -> envlist;
    while (env)
    {
        env = env -> next;
        i++;
    }
    dest = malloc(sizeof(char *) * (i + 1));
    if (!dest)
    return NULL;
    env = data -> envlist;
    i = 0;
    while (env)
    {   
        dest[i] = env -> str;
        i++;
        //printf("ouaisss : %s\n", dest[i]);
        env = env -> next;
    }
    dest[i] = NULL;
    //printf("la valeur de i [%d]\n", i);
    return dest;
}  