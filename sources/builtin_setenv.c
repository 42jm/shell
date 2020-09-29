//builtin_setenv.c//////////////////////////////////////////////////////////////

#include "minishell.h"

int		builtin_setenv(int argc, char **argv, t_list *envlst)
{
	t_list	*entry;

	if (argc > 3)
		return (put_error("too many arguments", *argv));
	if (argc > 1)
		return (env_set(envlst, argv[1], argv[2]));	
	env_put(envlst);
	return (0);
}
