#include "minishell.h"

int identifie_builtin(char *arg)
{
    if (!arg)
        return 1;
    if (ft_strncmp("cd", arg, 2) == 0)
        return 0;
    else if (ft_strncmp("echo", arg, 5) == 0)
        return 0;
    else if (ft_strncmp("env", arg, 3) == 0)
        return 0;
    else if (ft_strncmp("export", arg, 6) == 0)
        return 0;
    else if (ft_strncmp("pwd", arg, 3) == 0)
        return 0;
    else if (ft_strncmp("unset", arg, 5) == 0)
        return 0;
    else if (ft_strncmp("exit", arg, 5) == 0)
        return 0;
    return 1;
}

int start_builtins(t_data *data, t_cmd *cmd)
{
    char *arg;
    int exit;

    arg = cmd -> param[0];
    if (ft_strncmp("cd", arg, 2) == 0)
       exit = ft_cd(cmd , data);
    else if (ft_strncmp("echo", arg, 5) == 0)
        exit = ft_echo(cmd);
    else if (ft_strncmp("env", arg, 3) == 0)
        exit = ft_env(cmd, data);
    else if (ft_strncmp("export", arg, 6) == 0)
       exit = export_all(cmd, data);
    else if (ft_strncmp("pwd", arg, 3) == 0)
        exit = ft_pwd(cmd);
    else if (ft_strncmp("unset", arg, 5) == 0)
        exit = unset_all(cmd, data);
    else if (ft_strncmp("exit", arg, 5) == 0)
        exit = ft_exit(cmd , data);
    return exit;
}


void init_pipe(t_cmd *command)
{
    t_cmd *cmd;

    cmd = command;
    while (cmd)
    {
        if (cmd -> next || !cmd -> next && cmd -> prev)
        {
            if (pipe(cmd -> fd) == -1)
            {
                printf("error");
                exit(0);
            }
        }
        cmd = cmd -> next;
    }
}

void wait_child(t_data *data)
{
    int status;
    pid_t wait;

    wait = 0;
    close_fd(data -> cmd,NULL);
    while(wait != -1)
    {
        wait = waitpid(-1, &status, 0);

        if (wait == data -> pid)
        {
            if (WIFEXITED(status))
            {
                exit_codes = WEXITSTATUS(status);
            }
        }
    }    
}


int exec(t_data *data, t_cmd *cmd)
{
    if (cmd && !cmd -> prev && !cmd -> next && identifie_builtin(cmd -> param[0]) == 0)
    {
       exit_codes = start_builtins(data, cmd);
    }
    else
    {
        data -> cmd = cmd;
        init_pipe(cmd);
        while (cmd)
        {
            data -> pid = fork();
            if (data -> pid == 0 && !cmd -> skip)
                child_process(cmd, data);
            cmd = cmd -> next;
        }
        wait_child(data);
    }
    //usleep(100000);
    //printf("fini\n");   
}