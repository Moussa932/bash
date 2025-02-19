#include "minishell.h"

bool valide_dquote(char *str)
{
    int i;
    char c;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            c = str[i];
            i++;
            while (str[i])
            {
                if (str[i] == c)
                    return true;
                i++;
            }
        }
        i++;
    }
    return false;
}



char *quote_handler(char *str)
{
    int i;
    int nb;
    char *dest;

    i = -1;
    nb = 0;
    while (str[++i])
        if (str[i] == '\'' || str[i] == '\"')
            nb++;
    dest = malloc(sizeof(char) * (ft_strlen(str) - nb) + 1);
    if (!dest)
        return NULL;
    i = 0;
    nb = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
        {
            dest[nb++] = str[i];
            //printf("%c\n", dest[nb - 1]);
            //nb++;
        }
        i++;
    }
    dest[nb] = '\0';
    //printf("%s\n", dest);
    //printf("c chaud mgl");
    //exit(0);
    return dest;    
}

void quote_destroyer(t_token *token)
{
    t_token *tok;
    char *tmp;

    tok = token;
    while (tok)
    {
        if (valide_dquote(tok -> str))
        {
            //rintf("%sLLLLLLLLL", tok -> str);
            tmp = tok -> str;
            tok -> str = quote_handler(tok -> str);
            free(tmp);
        }
        tok = tok -> next;
    }
   //printf("%s", tok -> str);
}

void set_quote(t_token *token)
{
    t_token  *tok;
    int i;

    tok = token;
    while(tok)
    {
        i = 0;
        while (tok -> str[i])
        {
            if (tok -> str[i] == '\'')
                tok -> quote = SQUOTE;
            else if (tok -> str[i] == '\"')
                tok -> quote = DQUOTE;
        
            i++;
        }
        tok = tok -> next;
    }
}