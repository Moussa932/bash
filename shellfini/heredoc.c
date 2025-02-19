#include "minishell.h"

bool get_line(int fd, char *delimiter, t_data *data)
{
    char *line;
    t_env *envi;
    int i;
    
    envi = data -> envlist;
    while (1)
    {
        line = readline("heredoc>");
        if (exit_codes == 130)
            return false;
        if (ft_strncmp(line, delimiter, INT_MAX) == 0)
            break;
        i = 0;
        while (line[i])
        {
            if (line[i] == '$')
                set_var_value(&line, &envi, i, data -> exit_code);
            i++;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
    }
    return true;
}

int set_heredoc(char *str, t_cmd *cmd, t_data *data)
{
    char *delimiter;
    int fd;

    delimiter = str;
    fd = open("heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        return fd;
    if (!get_line(fd, delimiter, data))
        cmd -> skip = true;
    fd = open("heredoc_tmp.txt", O_RDONLY, 0644);
    if(fd > 0)
        unlink("heredoc_tmp.txt");
    return fd;
}