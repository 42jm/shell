/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/03/30 19:36:07 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "quegonza.h"

int 	ft_cd_options(char **argv)
{
	int	i;
	int	j;
	int	p_opt;

	i = 1;
	p_opt = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'L')
				p_opt = 0;
			else if (argv[i][j] == 'P')
				p_opt = 1;
			else
			{
				ft_bad_option(argv[0], argv[i][j], "invalid option");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (p_opt);
}

char 	*ft_get_link(char *path)
{
	struct stat	sb;
	char		*link;

	if (lstat(path, &sb) == -1)
	{
		ft_putstr("lstat: error: ");
		ft_putstr(path);
		return (NULL);
	}
	if ((sb.st_mode & S_IFMT) == S_IFLNK)
	{
		link = ft_memalloc(256);
		if (readlink(path, link, 256) == -1)
		{
			ft_putstr("readlink: error: ");
			ft_putstr(path);
			return (NULL);
		}
		free(path);
		return (link);
	}
	return (NULL);
}

char 	*ft_resolve_links(char *path)
{
	char	*res;
	char	*subpath;
	char	*tmp;
	int		i;

	i = 0;
	subpath = ft_memalloc(256);
	while (path[++i])
	{
		if (path[i] == '/')
		{
			ft_bzero(subpath, 256);
			ft_strncpy(subpath, path, i);
			res = ft_get_link(subpath);
			if (res)
			{
				tmp = path;
				path = ft_strjoin(res, &path[i]);
				free(tmp);
				i = 0;
			}
		}
	}
	free(subpath);
	return (path);
}

int 	builtin_cd_rest(int argc, char **argv, char *path, int opt)
{
	int	ret;

	if (ft_valid_dir(path, argv[argc - 1]))
	{
		ret = chdir(path);
		if (ret)
			return (put_error(path, "chdir() failed"));
	}
	if (opt == 1)
		path = getcwd(NULL, 0);
	else
		path = ft_resolve_path(path);
	env_set("OLDPWD", env_getvalue("PWD"), 0);
	env_set("PWD", path, 1);
	if (argc > 1 && !ft_strcmp(argv[argc - 1], "-"))
		ft_putendl(path);
	free(path);
	return (0);
}

int 	builtin_cd(int argc, char **argv)
{
	char	*path;
	int		ret;
	int		opt;

	opt = ft_cd_options(argv);
	if (opt == -1)
		return (ft_error("usage: cd [-L|-P] [directory]\n", 1));
	ret = ft_count_args(argc, argv);
	if (ret > 1)
		return (put_error("Too many arguments", *argv));
	if (ret == 0)
		path = env_getvalue("HOME");
	else if (!ft_strcmp(argv[argc - 1], "-"))
		path = env_getvalue("OLDPWD");
	else
		path = argv[argc - 1];
	return (builtin_cd_rest(argc, argv, path, opt));
}
