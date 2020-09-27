//prompt.c//////////////////////////////////////////////////////////////////////

#include "minishell.h"

int	put_prompt(int fd)
{
	if (pr_putstr_fd("$> ", fd) > 0)
		return (put_error("could not print prompt", NULL));
	return (0);
}
