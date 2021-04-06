/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:29:10 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/06 01:20:00 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_exist(char *path, char *arg)
{
	if (access(path, F_OK) == -1)
	{
		ft_put2str_fd(arg, ": file or directory does not exist\n", 2);
		return (0);
	}
	return (1);
}

int 	ft_valid_dir(char *path, char *arg)
{
	struct stat	sb;
	int			i;

	if (!ft_exist(path, arg))
		return (0);
	i = stat(path, &sb);
	if (!S_ISDIR(sb.st_mode))
	{
		ft_put2str_fd(arg, ": not a directory\n", 2);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		ft_put2str_fd(arg, ": permission denied\n", 2);
		return (0);
	}
	return (1);
}

int 	ft_valid_file(char *path, char *arg)
{
	struct stat	sb;
	int			i;

	if (!ft_exist(path, arg))
		return (0);
	i = stat(path, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_put2str_fd(arg, ": is a directory\n", 2);
		return (0);
	}
	if (!S_ISREG(sb.st_mode))
	{
		ft_put2str_fd(arg, ": not a regular file\n", 2);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		ft_put2str_fd(arg, ": permission denied\n", 2);
		return (0);
	}
	return (1);
}
