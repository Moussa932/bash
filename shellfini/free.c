#include "minishell.h"

void free_cmd(t_data *data)
{
    t_cmd *cmd;
    t_cmd *tmp;

    cmd = data -> cmd;
    while (cmd)
    {
        tmp = cmd;
        cmd = cmd -> next;
        free(tmp);
    }
}

void free_token(t_data *data)
{
    t_token *tok;
    t_token *tmp;

    tok = data -> token;
    while (tok)
    {
        tmp = tok;
        tok = tok -> next;
        free(tmp);
    }
}

void free_str(t_data *data)
{
    t_token *tok;

    tok = data -> token;
    while (tok)
    {
        free(tok -> str);
        tok = tok -> next;
    }
}

void free_all(t_data *data)
{
    free_str(data);
    free_cmd(data);
    free_token(data);
}