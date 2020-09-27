//builtin_echo.c////////////////////////////////////////////////////////////////////////

#include "minishell.h"

int	builtin_echo(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		pr_putstr_fd(argv[i], 1);
		if (++i < argc)
			pr_putstr_fd(" ", 1);
	}
	pr_putstr_fd("\n", 1);
	return (0);
}
