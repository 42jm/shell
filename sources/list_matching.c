/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_matching.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 01:26:23 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/06 14:28:21 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

t_list	*ft_ifalias(char *name)
{
	int		len;
	t_alias	*i;
	t_list	*res;

	len = ft_strlen(name);
	res = NULL;
	if (!name)
		return (NULL);
	i = g_alias;
	while (i)
	{
		if (ft_strnequ(name, i->name, len))
		{
			ft_lstadd(&res, ft_lstnew(i->name, ft_strlen(i->name) + 1));
		}
		i = i->next;
	}
	return (res);
}

t_list	*ft_ifbuiltin(char *name)
{
	int			i;
	int			len;
	t_list		*res;
	static char	*builtin[] = {
		"alias", "unalias", "pwd", \
		"echo", "exit", "cd", \
		"set", "unset", "export", \
		"setenv", "unsetenv", "env", \
		"jobs", "fg", "bg", NULL};

	len = ft_strlen(name);
	res = NULL;
	if (!name)
		return (NULL);
	i = -1;
	while (builtin[++i])
	{
		if (ft_strnequ(name, builtin[i], len))
		{
			ft_lstadd(&res, ft_lstnew(builtin[i], ft_strlen(builtin[i]) + 1));
		}
	}
	return (res);
}

t_list	*ft_match_filename(char *dir_name, char *bin_name)
{
	t_list			*res;
	DIR				*dir;
	struct dirent	*dirstream;
	int				len;

	len = ft_strlen(bin_name);
	dir = opendir(dir_name);
	if (!dir)
		return (NULL);
	res = NULL;
	dirstream = readdir(dir);
	while (dirstream)
	{
		if (ft_strnequ(dirstream->d_name, bin_name, len))
		{
			ft_lstadd(&res, ft_lstnew(dirstream->d_name, \
				ft_strlen(dirstream->d_name) + 1));
		}
		dirstream = readdir(dir);
	}
	closedir(dir);
	return (res);
}

t_list	*ft_ifbin(char *name)
{
	t_list	*res;
	t_list	*lst;
	char	**path_dirs;
	char	*path;
	int		i;

	path = env_getvalue("PATH");
	if (!path)
		return (NULL);
	path_dirs = ft_strsplit(path, ':');
	if (!path_dirs)
		return (NULL);
	res = NULL;
	i = -1;
	while (path_dirs[++i])
	{
		lst = ft_match_filename(path_dirs[i], name);
		if (lst)
		{
			ft_lstappend(&res, lst);
		}
	}
	ft_free_tabzero(path_dirs);
	return (res);
}
