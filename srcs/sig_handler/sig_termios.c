#include "../../headers/minishell.h"

void	ter_attr_handler_off(void)
{
	struct termios	save;
	struct termios	attr_new;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr_new);
	attr_new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &attr_new);
}

void	ter_attr_handler_on(void)
{
	struct termios	save;
	struct termios	attr_new;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &attr_new);
	attr_new.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &attr_new);
}
