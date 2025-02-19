#include "minishell.h"

t_cmd *last_cmd(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd != NULL && cmd -> next == NULL)
            return cmd;
        cmd = cmd -> next;
    }
    return cmd;
}

void add_cmd(t_cmd **cmd)
{
    t_cmd *last_node;
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return ;
    memset(node, 0, sizeof(t_cmd));
    node -> skip = false;
    node -> outfile = -2;
    node -> infile = -2;
    if (!(*cmd))
    {
        //printf("la valeur\n ");
        (*cmd) = node;
        return ;
    }
    else
    {
        last_node = last_cmd((*cmd));
        last_node -> next = node;
        node -> prev = last_node;
    }
    //return node;
}

int param_length(t_token *token)
{
    int i;

    i = 0;
    while (token && token -> type != PIPE && token -> type > 5)
    {
        //printf("HAHA BATARD\n");
        if (token -> type == CMD || token -> type == ARG || token -> type == VAR)
            i++;
        /*if (token -> next == NULL)
            break;*/
        token = token -> next;
    }
    return (i);
}