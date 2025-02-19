#include "minishell.h"

int exit_codes = 0;

int length_command(char *line)
{
    int i;
    bool quote;

    quote = false;
    i = 0;
    while (line[i] && !is_space(line[i]) && !is_token(line[i]))
    {
        if (line[i] == '"' || line[i] == '\'')
        {
           i++;
           while (line[i])
           {
                while (line[i] != '"' && line[i] != '\'' && line[i] && line[i] != ' ')
                    i++;
                if (line[i] == '"' || line[i] == '\'')
                    quote = true;
                if (end_token(line, i, quote))
                    return i;
                i++;
           }
        }
        if (!line[i])
          break;
        i++;
    }
    return (i);
}

void *string_management(char *s, int *i,t_token **token)
{
    int end;
    char *dest;
    int k;
    t_token *last;

    k = 0;
    end = length_command(s);
    dest = malloc(sizeof(char) * end + 1);
    if (!dest)
        return NULL;
    while (k < end)
    {
        dest[k] = s[k];
        k++;
    }
    dest[k] = '\0';
    add_token(token, CMD, dest, i);
    last = ft_last((*token));
    if (last-> prev == NULL || last -> prev -> type == PIPE)
        last -> type = CMD;
    else
        last -> type = ARG;
}

void identifie_token(char *line, int *i, t_token **token)
{
    char *s;
    s = line + *i;
    if (ft_strncmp(s, "<<", 2)== 0)
        add_token(token, HEREDOC, "<<",i);
    else if (ft_strncmp(s, ">>", 2) == 0)
        add_token(token, APPEND, ">>",i);
    else if (ft_strncmp(s, ">", 1) == 0)
        add_token(token, TRUNC, ">",i);
    else if (ft_strncmp(s, "<" , 1) == 0)
        add_token(token, INPUT, "<", i);
    else if (ft_strncmp(s, "|", 1)== 0)
        add_token(token, PIPE, "|", i);
    else
        string_management(s, i, token);  
}

void data_init(t_data *data, char **env)
{
    memset(data, 0, sizeof(t_data));
    data -> env = env;
    init_env(data -> env, &data -> envlist);
    data -> save_stdin = dup(STDIN_FILENO);
    data -> save_stdout = dup(STDOUT_FILENO);
}

void lexer(t_token *token, char *line, t_data *data)
{
    int i;
    
    i = 0;

    while (line[i])
    {
        while (line[i] && is_space(line[i]) == true)
            i++;
        if (line[i] == '\0')
            break;
        identifie_token(line, &i, &token);
    }
    set_quote(token);
    set_var(token);
    quote_destroyer(token);
    data -> token = token;
}

bool check_line(char *s)
{
    int i;

    i = 0;
    if (!s)
      return false;
    while (s[i] && is_space(s[i]))
        i++;
    if (i == ft_strlen(s))
    {
        free(s);
        //printf("oausdasddasads\n");
        return false;
    }
    return true;
}
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_token *p;
    t_data data;
    char **arg = env;
   
    int i = 0;
    p = NULL;
    char *line;
    set_signal();
    //data_init(&data, env);
    while(1)
    {
        data_init(&data, arg);
        line = readline("minishell>");
        if (!check_line(line))
            continue;
        add_history(line);
        lexer(p, line, &data);
        var_expansion(&data);
        //printf("LINEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
        if(!create_command(&data))
        {
            free_all(&data);
            continue;
        }
        exec(&data, data.cmd);
        arg = copy_arg_env(&data);
        free_all(&data);
        //usleep(1000000);
        //exit(0);
        /*p = data.token;
        while(p)
        {
            printf("string : %s type : %d  \n",p -> str, p -> type);

            p = p -> next;
            i++;
        }*/
    }
   
   //exec(&data);
   //set_path_cmd("grep", data.envlist);
   //exit(0);
   while (data.envlist)
    {
        printf("%s\n", data.envlist -> str);
        data.envlist = data.envlist -> next;
    }
    exit(0);
   
    while(p)
    {
     printf("string : %s type : %d  \n",p -> str, p -> type);
     p = p -> next;
     i++;
    }
   
}

//gcc expanser.c expanser_utils.c signal.c lexer.c lexer_utils.c libc.c quote.c export_utils.c heredoc.c command.c command_utils.c exec2.c exec.c ft_cd.c free.c ft_echo.c ft_env.c ft_export.c ft_pwd.c ft_unset.c path_cmd.c -lreadline