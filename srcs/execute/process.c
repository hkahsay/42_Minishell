#include "../../headers/minishell.h"

if (fork() == 0)
{
	execve(path, argv, ennvp);
}
else
{
	waitpid()
}