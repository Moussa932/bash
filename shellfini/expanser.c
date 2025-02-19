#include "minishell.h"

char *copy_env(t_env **env, char *var)
{
    int i;
    int size;
    int len;

    i = -1;
    len = 0;
    size = ft_strlen(var);
    while ((*env))
    {
        if (ft_strncmp((*env) -> str, var, size) == 0)
        {
            while((*env) -> str[len] && (*env) -> str[len] != '=')
                len++;
            return (ft_strdup((*env) -> str + len + 1));
        }
        (*env) = (*env) -> next;
    }
    return NULL;
}

void seconde_update_string(int *j, char *dest, char *replace)
{
    int k;

    k = 0;
    while (replace[k])
    {
        dest[*j] = replace[k];
        k++;
        (*j)++;
    }
}

bool for_the_norm(int *i, int *j, char *str, char *dest)
{
    dest[*j] = str[*i];
    if (!str[*i])
        return false;
    i++;
    j++;
    return true;
}



char *update_string(char *str, char *replace, char *var, int index)
{
    int size;
    char *dest;
    int i;
    int j;
    
    i = -1;
    j = 0;
    size = ft_strlen(str) - (ft_strlen(var) + 1) + ft_strlen(replace);
    dest = malloc(sizeof(char) * size + 1);
    if (!dest)
        return NULL;
    while (str[++i])
    {
        if (str[i] == '$' && i == index)
        {
            seconde_update_string(&j, dest, replace);
            i += ft_strlen(var) + 1;
        }
        if (!for_the_norm(&i, &j, str, dest))
            break;
    }
    dest[j] = '\0';
    return dest; 
}

void set_var_value(char **str, t_env **env, int index, int exit_code)
{
    char *var;
    char *replace;
    char *copy;

    copy = *str;
    var = var_isolation(copy, index);
    if (var_in_env(var, env))
    {
        replace = copy_env(env, var);
        *str = update_string(copy, replace, var, index);
    }
    else if(var[0] == '?')
    {
        replace = ft_itoa(exit_codes);
        *str = update_string(copy, replace, var, index);
    }
    else
        *str = ft_strdup(""); 
}

void var_expansion(t_data *data)
{
    t_token *tok;
    int i;
    t_env *envi;

    tok = data -> token;
    envi = data -> envlist;
    while (tok)
    {
        i = -1;
        if (tok -> type == VAR  && tok -> quote != SQUOTE)
        {
            while (tok -> str[++i])
            {
                if (tok -> str[i] == '$')
                    set_var_value(&tok -> str, &envi, i, data -> exit_code);
                if (!tok -> str[i])
                    break;
            }
        }
        tok = tok -> next;
    }
}

/*void var_expansion(t_data *data)
{
    t_token *tok;
    t_env *envi = data -> envlist;
    int i;
    tok = data -> token;
    set_quote(tok);
    set_var(tok);
    while (tok)
    {
        i = -1;
        if (tok -> type == VAR  && tok -> quote != SQUOTE)
        {
            while (tok -> str[++i])
            {
                if (tok -> str[i] == '$')
                {
                    set_var_value(&tok -> str, &envi, i, data -> exit_code);
                    //printf("token   : %s\n", tok -> str);
                }
            }
        }
        tok = tok -> next;
    }
    
    quote_destroyer(data -> token);
}*/