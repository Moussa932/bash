#include "minishell.h"

char **get_param(t_cmd *cmd, t_token *token)
{
    char **param;
    int i;
    //t_token *leng;

    i = 0;
    //printf("%d\n",  param_length(token) + 1);
    //exit(0);
    param = malloc(sizeof(char *) * (param_length(token) + 1));
    if (!param)
        return NULL;
    while (token && token -> type != PIPE && token -> type > 5)
    {
         if (token -> type == CMD || token -> type == ARG || token -> type == VAR)
         {
            param[i] = ft_strdup(token -> str);
            i++;
         }
         /*if (token -> next == NULL)
            break;*/
         token = token -> next;
    }
    param[i] = NULL;
    return param;
}

bool get_outfile_fd(t_token *tok, t_cmd *cmd)
{
    char *str;

    if (cmd -> outfile >= 0)
    close(cmd -> outfile);
    if (!tok -> next || tok -> next -> type <= 5)
    {
        ft_putstr_fd("parse error\n", STDERR_FILENO);
        exit_codes = 2;
        return false;
    }
    str = tok -> next -> str;
    if (tok -> type == APPEND)
        cmd -> outfile = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        cmd -> outfile = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (cmd -> outfile == -1)
    {
        printf("%s\n", strerror(errno));
        return (false);
    }
    return (true);
}


bool get_infile_fd(t_token *tok, t_cmd *cmd, t_data *data)
{
    char *str;
    if (cmd -> infile >= 0)
    close(cmd -> infile);
    if (!tok -> next || tok -> next -> type <= 5)
    {
        ft_putstr_fd("parse error\n", STDERR_FILENO);
        exit_codes = 2;
        return false;
    }
    str = tok -> next -> str;
    if (tok -> type == INPUT)
        cmd -> infile = open(str, O_RDONLY, 0644);
    else
        cmd -> infile = set_heredoc(str, cmd, data);
    if (cmd -> infile == -1)
    {
        printf("%s\n", strerror(errno));
        return (false);
    }
    return (true);
}

bool set_command(t_cmd **cmd, t_token *token, t_data *data)
{
    t_token *tok;
    t_cmd *command;

    add_cmd(cmd);
    command = last_cmd((*cmd));
    tok = token -> next;
    while (tok && tok -> type != PIPE )
    {
        if (tok -> type == APPEND || tok -> type == TRUNC)
        {
            if(!get_outfile_fd(tok, command))
                return false;
        }
        else if (tok -> type == HEREDOC || tok -> type == INPUT)
        {
                if(!get_infile_fd(tok, command, data))
                    return false;
        }
        tok = tok -> next;
    }
    command -> param = get_param((*cmd), token);
    return true;
}

bool create_command(t_data *data)
{
    t_cmd *cmd;
    t_token *token;

    cmd = data -> cmd;
    token = data -> token;
    if (token)
        if(!set_command(&cmd, token, data))
            return false;
    token = token -> next;
    while (token)
    {
        if (token -> type == CMD || token -> prev -> type == PIPE)
        {
            if(!set_command(&cmd, token , data))
                return false;
        }
        token = token -> next;
    }
    data -> cmd = cmd;
    return true;
    /*while (cmd)
    {
        i = 0;
        while (cmd -> param[i])
        {
         //printf("la valeur %d cmd infile %d\n", i, cmd ->infile);
         //printf("la valeur %d cmd outfile %d\n", i, cmd ->outfile);
             printf("%s\n", cmd -> param[i]);
        //cmd = cmd -> next;
        //printf("%s\n", cmd ->command[i]);
            //printf("%d\n", i);
            i++;
        }
        if (cmd -> next == NULL)
            break;
        cmd = cmd -> next;
        printf("next cmd\n");
    }
    */
    //exec(data, cmd);
    //ft_echo(cmd);
    //ft_export(cmd, data);
    //ft_unset(cmd, data);
    //ft_cd(cmd , data);
    //ft_exit(cmd,data);
    //ft_env(cmd, data);
    //ft_pwd(cmd);
    //exit(0);
    //printf("la valeur %d", i);
}