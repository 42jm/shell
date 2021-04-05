/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:41:55 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/03 02:44:07 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "quegonza.h"

char	*ft_path(char *path, char *name)
{
	char	*new_path;
	int		s1;
	int		s2;

	s1 = ft_strlen(path);
	s2 = ft_strlen(name);
	if (path[s1 - 1] != '/')
	{
		new_path = (char *)ft_memalloc(s1 + s2 + 2);
		if (!new_path)
			return (NULL);
		ft_strncpy(new_path, path, s1);
		new_path[s1] = '/';
		ft_strncpy(&new_path[s1 + 1], name, s2);
	}
	else
	{
		new_path = (char *)ft_memalloc(s1 + s2 + 1);
		if (!new_path)
			return (NULL);
		ft_strncpy(new_path, path, s1);
		ft_strncpy(&new_path[s1], name, s2);
	}
	return (new_path);
}

char	*ft_find_filename(char *dir_name, char *bin_name)
{
	DIR				*dir;
	struct dirent	*dirstream;

	dir = opendir(dir_name);
	if (!dir)
		return (NULL);
	dirstream = readdir(dir);
	while (dirstream)
	{
		if (!ft_strcmp(dirstream->d_name, bin_name))
		{
			closedir(dir);
			return (ft_path(dir_name, bin_name));
		}
		dirstream = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*ft_get_path(char *name)
{
	char	*res;
	char	**path_dirs;
	int		i;

	res = env_getvalue("PATH");
	if (!res)
		return (NULL);
	path_dirs = ft_strsplit(res, ':');
	if (!path_dirs)
		return (NULL);
	i = -1;
	while (path_dirs[++i])
	{
		res = ft_find_filename(path_dirs[i], name);
		if (res)
		{
			ft_free_tabzero(path_dirs);
			return (res);
		}
	}
	ft_free_tabzero(path_dirs);
	return (NULL);
}
