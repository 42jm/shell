//error.c///////////////////////////////////////////////////////////////////////

#include "minishell.h"

int	put_error_ret(char *message, char *arg, int ret)
{
	pr_putstr_fd("minishell: ", 2);
	pr_putstr_fd(message, 2);
	if (arg)
	{
		pr_putstr_fd(" -- ", 2);
		pr_putstr_fd(arg, 2);
	}
	pr_putstr_fd("\n", 2);
	return (ret);
}

int	put_error(char *message, char *arg)
{
	return (put_error_ret(message, arg, 1));
}
