#include "../../headers/minishell.h"

/*
void rl_replace_line(const char *text, int clear_undo)
text: that specifies the new line to replace the current contents of the input buffer.
clear_undo: If clear_undo is non-zero (e.g., 1), will be cleared
if clear_undo is zero (e.g., 0), the undo history will be preserved.
void rl_on_new_line(void) indicate the cursor has moved on a new line
void rl_redisplay(void)used to redisplay the current contents of input buffer after making changes
*/
void	ter_attr_handler(struct termios save)
{
	struct termios attr;
	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, &save);
}

void sig_handlers(void)
{
	// int	pid;
	// struct sigaction sa;
	// sa.sa_handler = &sigint_handler;
	// sigaction(SIGINT, &sa, NULL);
	signal(EOF, sig_quit_handler);
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, sig_do_nothing);
	// signal(SIGSTOP, sig_do_nothing);


}

void	sigint_handler(int	sig_num)
{
	if(sig_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	sig_quit_handler(int sig_num)
{
	// (void)sig_num;
	sigint_handler(sig_num);
	write(1, "exit", 4);
}

void	sig_do_nothing(int sig_num)
{
	(void)sig_num;
}
	// printf("ctr.d is pressed its exiting the prompt and print exit\n");
	// write(1, "\n", 1);
	// write(1, "exit", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();