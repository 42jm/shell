/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 19:06:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static char	*cd_fullpath(char *directory)
{
	char	*curpath;
	char	*cwd;

	if (*directory == '/')
		return (ft_strdup(curpath));
	if (!(cwd = getcwd(NULL, 0)))
		return (NULL);
	if (!*cwd)
		return (NULL);
	if (cwd[ft_strlen(cwd) - 1] != '/')
		curpath = ft_strcjoin(cwd, '/', directory);
	else
		curpath = ft_strjoin(cwd, directory);
	free(cwd);
	return (curpath);
}

static int	cd_chdir(char *directory, char *options)
{
	char	*curpath;
	char	opt;
	int		ret;

	opt = 'L';
	if (*options)
		opt = options[ft_strlen(options) - 1];
	if (!(curpath = cd_fullpath(directory)))
		return (1);
	if (opt == 'L')
	{
		
	}
	ret = chdir(curpath);
	free(curpath);
	return (ret);
}

static char	*cd_getpath(int argc, char **argv, int *verbose)
{
	char	*path;

	if (argc > 1)
	{
		put_error("Too many arguments", "cd");
		ft_putusage("cd", "[-L|-P] [dir]");
		return (NULL);
	}
	if (argc == 0)
		path = env_getvalue("HOME");
	else if (!ft_strcmp(*argv, "-"))
	{
		*verbose = 1;
		path = env_getvalue("OLDPWD");
	}
	else
		path = *argv;
	return (path);
}

int			builtin_cd(int argc, char **argv)
{
	char	*path;
	char	*options;
	int		verbose;

	verbose = 0;
	if (!(options = ft_optset(&argc, &argv, "LP")))
		return (ft_putusage("cd", "[-L|-P] [dir]"))
	if (!(path = cd_getpath(argc, argv, &verbose)))
	{
		free(options);
		return (1);
	}
	if (cd_chdir(path, options))
	{
		free(options);
		return (put_error("Chdir failed", "cd"));
	}
	path = getcwd(NULL, 0);
	env_set("OLDPWD", env_getvalue("PWD"), 0);
	env_set("PWD", path, 1);
	if (verbose)
		ft_putendl(path);
	free(path);
	free(options);
	return (0);
}
