#include "minishell.h"

void sighandler()
{
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    exit_codes = 130;
}

void set_signal()
{
    signal(SIGINT, &sighandler);
}

/*void sigheredoc()
{
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    global = 1;
}

int heredoc_signal()
{
    signal(SIGINT, &sigheredoc);
}*/