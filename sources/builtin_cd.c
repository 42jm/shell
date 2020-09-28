//builtin_cd.c//////////////////////////////////////////////////////////////////

#include "minishell.h"

int	builtin_cd(int argc, char **argv, t_list *envlst)
{
	char	*path;
	
	if (argc > 2)
		return (put_error("too many arguments", *argv));
	if (argc == 1)
		path = env_getvalue(envlst, "HOME");
	else if (!ft_strcmp(argv[1], "-"))
		path = env_getvalue(envlst, "OLDPWD");
	else
		path = argv[1];
	chdir(path);
	if (!ft_strcmp(argv[1], "-"))
		ft_putendl(env_getvalue(envlst, "PWD"));
	return (0);
}
