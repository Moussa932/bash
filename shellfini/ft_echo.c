#include "minishell.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	write(fd, s, i);
}

static bool check_new_line(char *str)
{
    int i;

    i = 0;
    
    if (str[i] == '-')
    {
        i++;
        while (str[i] && str[i] == 'n')
        {
            i++;
            if (str[i] == '\0')
            {
               return true;
            }
        }
    }
    return false;
}

static void write_in_fd(bool newline, char **param, int fd)
{
    int i;

    i = 1;
    while(param[i] && check_new_line(param[i]) == true)
        i++;
    while(param[i])
    {
        ft_putstr_fd(param[i], fd);
        if (param[i + 1] != NULL)
        {
            //printf("NOUSYEST\n");
            ft_putstr_fd(" ", fd);
        }
        i++;
    }
    if(!newline)
        ft_putstr_fd("\n", fd);

}

static int pick_fd(t_cmd *cmd)
{
    int fd;

    fd = 1;

    if (cmd -> infile >= 0)
        fd = cmd -> infile;
    else if (cmd -> outfile >= 0)
        fd = cmd -> outfile;
    return fd;
}


int ft_echo(t_cmd *cmd)
{
    int fd;
    bool newline;
    char **param = cmd -> param;

    if (!param[1])
    {
        printf("\n");
        return (0);
    }
    fd = pick_fd(cmd);
    newline = check_new_line(cmd -> param[1]);
    write_in_fd(newline, param, fd);
    //write_in_fd(newline, param, cmd -> fd[1]);
    //dup2(cmd -> fd[1], cmd -> outfile);
    return (0);
}