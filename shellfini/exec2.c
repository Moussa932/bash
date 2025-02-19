#include "minishell.h"

void close_fd(t_cmd *command, t_cmd *actual_fd)
{

    while (command)
    {
        if (command != actual_fd)
        {
            close(command -> fd[0]);
            close(command -> fd[1]);
        }
        command = command -> next;
    }
}

void set_pipe(t_cmd *cmd, t_cmd *command)
{
    if (cmd -> infile > -1)
    {
        dup2(cmd ->infile, STDIN_FILENO);
        cmd -> fd[0] = cmd -> infile;
    }
    else if (cmd && cmd -> prev)
    {
        if (cmd -> prev)
            close(cmd -> prev -> fd[1]);
        dup2(cmd -> prev -> fd[0], STDIN_FILENO);
    }
    if (cmd && cmd -> next)
        dup2(cmd -> fd[1], STDOUT_FILENO);
    
    close_fd(command, cmd);
}



int child_process(t_cmd *command, t_data *data)
{
    char *cmd_path;
    int exit_c;

    set_pipe(command, data -> cmd);
    if (identifie_builtin(command -> param[0]) == 0)
    {
        exit_c = start_builtins(data, command);
        close(command -> fd[0]);
        close(command -> fd[1]);
        exit(exit_c);
    }
    cmd_path = set_path_cmd(command, data -> envlist);
    if (execve(cmd_path, command -> param, data -> env) == -1)
    {
        //printf("error");
       // exit(0);
    }
    close(command -> fd[0]);
    close(command -> fd[1]);
    dup2(data ->save_stdin, STDIN_FILENO);
    dup2(data -> save_stdout, STDOUT_FILENO);
    exit(0);

}