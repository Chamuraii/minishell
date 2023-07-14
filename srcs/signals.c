#include "../includes/minishell.h"

extern t_all g_all;

void	ft_sigint_handler()
{
	printf("\n");
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signals()
{
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}