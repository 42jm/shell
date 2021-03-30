/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:29:10 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/30 19:45:32 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_exist(char *path, char *arg)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr(arg);
		ft_putstr(": file or directory does not exist\n");
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
		ft_putstr(arg);
		ft_putstr(": not a directory\n");
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr(arg);
		ft_putstr(": permission denied\n");
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
		ft_putstr(arg);
		ft_putstr(": is a directory\n");
		return (0);
	}
	if (!S_ISREG(sb.st_mode))
	{
		ft_putstr(arg);
		ft_putstr(": not a regular file\n");
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr(arg);
		ft_putstr(": permission denied\n");
		return (0);
	}
	return (1);
}
