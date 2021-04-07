/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:29:10 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/31 18:03:37 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_exist(char *path, char *arg)
{
	if (access(path, F_OK) == -1)
	{
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": file or directory does not exist\n", 2);
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
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": not a directory\n", 2);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": permission denied\n", 2);
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
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": is a directory\n", 2);
		return (0);
	}
	if (!S_ISREG(sb.st_mode))
	{
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": not a regular file\n", 2);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		pr_putstr_fd(arg, 2);
		pr_putstr_fd(": permission denied\n", 2);
		return (0);
	}
	return (1);
}
