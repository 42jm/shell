//builtin_exit.c////////////////////////////////////////////////////////////////////////

#include "minishell.h"

void	builtin_exit(int argc, char **argv)
{
	int	i;

	pr_putstr_fd("exit\n", 2);
	if (argc > 2)
		put_error("too many arguments", *argv);
	i = 0;
	if (argc == 2)
	{
		if (ft_isdigit((int)argv[1][0]))
			i = ft_atoi(argv[1]);
		else
			put_error("numeric argument required", argv[1]);
	}
	exit(i);
}
