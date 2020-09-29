//builtin_cd.c//////////////////////////////////////////////////////////////////

#include "minishell.h"

int	builtin_cd(int argc, char **argv, t_list *envlst)
{
	char	*path;
	int		ret;
	
	if (argc > 2)
		return (put_error("too many arguments", *argv));
	if (argc == 1)
		path = env_getvalue(envlst, "HOME");
	else if (!ft_strcmp(argv[1], "-"))
		path = env_getvalue(envlst, "OLDPWD");
	else
		path = argv[1];
	ret = chdir(path);
	if (ret)
		return (put_error("chdir failed", *argv));
	path = getcwd(NULL, 0);
	env_set(envlst, "OLDPWD", env_getvalue(envlst, "PWD"));
	env_set(envlst, "PWD", path);
	if (argc > 1 && !ft_strcmp(argv[1], "-"))
		ft_putendl(path);
	free(path);
	return (0);
}
