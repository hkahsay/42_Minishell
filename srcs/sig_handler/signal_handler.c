#include "../../headers/minishell.h"


void	ter_attr_handler(struct termios *save)
{
	struct termios attr;

	tcgetattr(STDIN_FILENO, save);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, &save);
}

void	handle_signal(struct termios *saved)
{
	ter_attr_handler(saved);
	// sig_handlers();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
// void sig_handlers(void)
// {
// 	signal(EOF, sig_quit_handler);
// 	signal(SIGINT, &sigint_handler);
// 	// signal(SIGQUIT, SIG_IGN);
// 	signal(SIGSTOP, sig_do_nothing);


// }


void	sigint_handler(int	sig_num)
{
	if(sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// g_exit_status = 1;
	}
}

void	sig_quit_handler(int sig_num)
{
	// (void)sig_num;
	if (sig_num == SIGINT)
	{
		write (1, "\n", 1);
	}
	if (sig_num == SIGQUIT)
	{
		write(1, "exit", 4);
		rl_on_new_line();
	}
}

// void	sig_do_nothing(int sig_num)
// {
// 	(void)sig_num;
// }
// 	// printf("ctr.d is pressed its exiting the prompt and print exit\n");
// 	// write(1, "\n", 1);
// 	// write(1, "exit", 1);
// 	// rl_replace_line("", 0);
// 	// rl_on_new_line();
// 	// rl_redisplay();
// 	// rl_replace_line("", 0);
// 	// rl_on_new_line();
// 	// rl_redisplay();