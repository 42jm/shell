//builtin_cd.c//////////////////////////////////////////////////////////////////

#include "minishell.h"

int	builtin_cd(int argc, char **argv)
{
	if (argc > 2)
		put_error("too many arguments", *argv);
	else if (argc == 1)
		// cd "$HOME"
	else if (ft_strcmp(argv[1], "-"))
		// cd "$OLDPWD" && pwd
	else
		// cd argv[1]
	return (0);
}
