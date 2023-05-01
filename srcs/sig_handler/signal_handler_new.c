#include "../../headers/minishell.h"


void	ter_attr_handler_off(void)
{
	struct termios save;
	struct termios attr_new;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr_new);
	attr_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &attr_new);
}

void	ter_attr_handler_on(void)
{
	struct termios save;
	struct termios attr_new;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr_new);
	attr_new.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &attr_new);
}

void	signal_at_beginning(void)
{

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

void	signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// static mode
void	sigint_handler(int	sig_num)
{
	if(sig_num == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

// interactive mode
void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_exit_status = 1;
	}
}
